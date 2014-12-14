#include "GamesManager.hpp"
#include "GameException.hpp"
#include "GamesManagerException.hpp"
#include "GameProperties.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

GamesManager::GamesManager(void) : mThreadPool(ThreadPool::getInstance()), mMutex(PortabilityBuilder::getMutex()), mListener(nullptr) {
	mPlayerCommunicationManager.setListener(this);
}

GamesManager::~GamesManager(void) {
    mGames.clear();
    mThreadPool->stop();
}

void GamesManager::run(void) {
	mScriptLoader.loadAll();

    std::vector<std::shared_ptr<NGame::Game>> games;
    while (true)
    {
        {
            ScopedLock scopedLock(mMutex);

            games = mGames;
        }

		for (auto it = games.begin(); it != games.end();)
		{
            if ((*it)->getPullEnded() == true)
        		switch ((*it)->getState())
        		{
        		case NGame::Game::State::RUNNING:
                    (*it)->setPullEnded(false);
    				*mThreadPool << std::bind(&NGame::Game::pull, (*it));
        			break;
        		case NGame::Game::State::DONE:
        			terminatedGame(findGameByName((*it)->getProperties().getName()));
        			break;
                default:
                    break;
        		}

            ++it;
		}
    }
}

void GamesManager::createGame(const NGame::Properties& properties, const Peer &peer) {
    ScopedLock scopedLock(mMutex);

	if (findGameByName(properties.getName()) != mGames.end())
		throw GamesManagerException("Game name already taken", ErrorStatus(ErrorStatus::Error::KO));
	if (properties.getMaxPlayers() < 1 || properties.getMaxPlayers() > 4)
		throw GamesManagerException("Invalid max nb players", ErrorStatus(ErrorStatus::Error::KO));
	if (properties.getMaxSpectators() < 0 || properties.getMaxSpectators() > 4)
		throw GamesManagerException("Invalid max nb observers", ErrorStatus(ErrorStatus::Error::KO));
	if (mScriptLoader.isExist(properties.getLevelName()) == false)
		throw GamesManagerException("Invalid level name", ErrorStatus(ErrorStatus::Error::KO));
	auto game = std::make_shared<NGame::Game>(properties, mScriptLoader.getScript(properties.getLevelName()));

    game->setListener(this);
    game->setOwner(peer);

    mGames.push_back(game);
}

void GamesManager::removeGame(const Peer &peer, const std::string& name) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByName(name);

    if (game == mGames.end())
        throw GamesManagerException("Try to delete an undefined game", ErrorStatus(ErrorStatus::Error::KO));

	if (peer == (*game)->getOwner()) {
		removeClientsFromWhitelist(*game);
		mGames.erase(game);
	}
    else
        throw GamesManagerException("You can remove a game only if you are owner", ErrorStatus(ErrorStatus::Error::KO));
}

void	GamesManager::removeClientsFromWhitelist(const std::shared_ptr<NGame::Game> &game) {
	auto users = game->getUsers();

	std::for_each(users.begin(), users.end(), [&](const NGame::User& user) {
		mPlayerCommunicationManager.removePeerFromWhiteList(user.getPeer());
	});
}

/*
** PlayerCommunicationManager::OnPlayerCommunicationManagerEvent
*/ 
void GamesManager::onPlayerFire(PlayerCommunicationManager &playerCommunicationManager, const Peer &peer) {
	ScopedLock scopedLock(mMutex);

    try {
        auto game = findGameByHost(peer);

        if (game == mGames.end())
            throw GamesManagerException("Try to fire a player that is not in a game", ErrorStatus(ErrorStatus::Error::KO));
        
		try {
			auto component = (*game)->fire(peer);
			for (const auto &user : (*game)->getUsers())
				playerCommunicationManager.sendMoveResource(user.getPeer(), component.getId(), component.getType(), component.getX(), component.getY(), component.getAngle());
		}
		catch (const GameException& e) {
			std::cerr << "GameException caught: " << e.what() << std::endl;
		}
    }
    catch (const GamesManagerException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GamesManager::onPlayerMove(PlayerCommunicationManager &playerCommunicationManager, IResource::Direction direction, const Peer &peer) {
	ScopedLock scopedLock(mMutex);
    try {
        auto game = findGameByHost(peer);

        if (game == mGames.end())
            throw GamesManagerException("Try to move a player that is not in a game", ErrorStatus(ErrorStatus::Error::KO));

		try {
			auto component = (*game)->move(peer, direction);
			for (const auto &user : (*game)->getUsers())
				playerCommunicationManager.sendMoveResource(user.getPeer(), component.getId(), component.getType(), component.getX(), component.getY(), component.getAngle());
		}
		catch (const GameException& e) {
			std::cerr << "GameException caught: " << e.what() << std::endl;
		}
    }
    catch (const GamesManagerException& e) {
        std::cerr << e.what() << std::endl;
    }
}

/*
** Game::OnGameEvent
*/
std::vector<std::shared_ptr<NGame::Game>>::iterator GamesManager::terminatedGame(std::vector<std::shared_ptr<NGame::Game>>::iterator it) {
	if (mListener) {
		std::list<Peer> gameUsers;

		for (const auto &user : (*it)->getUsers()) {
			onNotifyUserGainScore(user.getPeer(), user.getId(), user.getPseudo(), user.getScore());
			gameUsers.push_back(user.getPeer());
		}

		mListener->onEndGame((*it)->getProperties().getName(), gameUsers);
	}

	removeClientsFromWhitelist(*it);
	return mGames.erase(it);
}

void GamesManager::onRemovePeerFromWhiteList(const Peer& peer) {
	ScopedLock scopedLock(mMutex);

	mPlayerCommunicationManager.removePeerFromWhiteList(peer);
}

void GamesManager::onNotifyUsersComponentRemoved(const std::vector<NGame::User>& users, uint64_t id) {
	ScopedLock scopedLock(mMutex);

	std::cout << __FUNCTION__ << std::endl;
	for (const auto &user : users)
		mPlayerCommunicationManager.sendDestroyResource(user.getPeer(), id);
}

void GamesManager::onNotifyUserGainScore(const Peer &peer, uint64_t id, const std::string &pseudo, uint64_t score) {
	ScopedLock scopedLock(mMutex);

	std::cout << __FUNCTION__ << std::endl;
	mPlayerCommunicationManager.sendUpdateScore(peer, id, pseudo, score);
}

void GamesManager::onNotifyTimeElapsedPing(const Peer &peer, double elapsedPing) {
	ScopedLock scopedLock(mMutex);

	std::cout << __FUNCTION__ << std::endl;
	mPlayerCommunicationManager.sendTimeElapsedPing(peer, elapsedPing);
}

void GamesManager::joinGame(NGame::USER_TYPE typeUser, const Peer &peer, const std::string &name, const std::string &pseudo) {
    std::cout << "DEBUG POUR UNIX [" << __FILE__ << "] [" << __LINE__ << "] [" << __FUNCTION__ << "] AVANT DEADLOCK" << std::endl;
    ScopedLock scopedLock(mMutex); // ce scoped lock deadlock sur unix pk je ne sais pas
    std::cout << "DEBUG POUR UNIX [" << __FILE__ << "] [" << __LINE__ << "] [" << __FUNCTION__ << "] APRES DEADLOCK" << std::endl;

    auto existingGame = findGameByHost(peer);
    if (existingGame != mGames.end())
      (*existingGame)->delUser(peer);

    auto game = findGameByName(name);
    if (game == mGames.end())
      throw GamesManagerException("Try to join an undefined game party name", ErrorStatus(ErrorStatus::Error::KO));
    (*game)->addUser(typeUser, peer, pseudo);
}

void GamesManager::playGame(const Peer &peer, const std::string &name, const std::string &pseudo) {
	ScopedLock scopedLock(mMutex);

    try {
        joinGame(NGame::USER_TYPE::PLAYER, peer, name, pseudo);
        mPlayerCommunicationManager.addPeerToWhiteList(peer);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::spectateGame(const Peer &peer, const std::string &name) {
	ScopedLock scopedLock(mMutex);

    try {
        joinGame(NGame::USER_TYPE::SPECTATOR, peer, name);
        mPlayerCommunicationManager.removePeerFromWhiteList(peer);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::leaveGame(const Peer &peer) {
    ScopedLock scopedLock(mMutex);

    try {
        auto game = findGameByHost(peer);

        if (game == mGames.end())
                throw GamesManagerException("Try to leave a player who isn't in a game", ErrorStatus(ErrorStatus::Error::KO));

        (*game)->delUser(peer);
        mPlayerCommunicationManager.removePeerFromWhiteList(peer);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::updatePseudo(const Peer &peer, const std::string &pseudo) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByHost(peer);

    if (game == mGames.end())
        throw GamesManagerException("Try to update pseudo of a non-existing player", ErrorStatus(ErrorStatus::Error::KO));

    try {
        auto user = (*game)->findUserByHost(peer);
        if (user == (*game)->getUsers().end())
            throw GameException("Try to update pseudo of a non-existing player");
        user->setPseudo(pseudo);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

const NGame::Properties &GamesManager::getGameProperties(const std::string &name) {
    ScopedLock scopedLock(mMutex);

    auto game = findGameByName(name);

    if (game == mGames.end())
        throw GamesManagerException("Try to get properties of an undefined game", ErrorStatus(ErrorStatus::Error::KO));

    return (*game)->getProperties();
}

std::list<NGame::Properties> GamesManager::getGamesProperties(void) const {
    ScopedLock scopedLock(mMutex);

	std::list<NGame::Properties> gamesProperties;

    for (const auto& game : mGames)
        gamesProperties.push_back(game->getProperties());

    return gamesProperties;
}

std::vector<std::shared_ptr<NGame::Game>>::iterator GamesManager::findGameByName(const std::string& name) {
    return std::find_if(mGames.begin(), mGames.end(), [&name](const std::shared_ptr<NGame::Game>& game) {
        return game.get()->getProperties().getName() == name;
    });
}

std::vector<std::shared_ptr<NGame::Game>>::iterator GamesManager::findGameByHost(const Peer &peer) {
    return std::find_if(mGames.begin(), mGames.end(), [&peer](const std::shared_ptr<NGame::Game>& game) {
        auto playersAddress = game.get()->getUsers();
        for (const auto& playerAddress : playersAddress) {
            if (playerAddress.getPeer() == peer)
                return true;
        }
        return false;
    });
}

std::list<std::pair<std::string, std::string>> GamesManager::getScripts(void) const {
	ScopedLock scopedLock(mMutex);

	std::list<std::pair<std::string, std::string>> scripts;

	for (const auto &script : mScriptLoader.getScripts())
		scripts.push_back(std::pair<std::string, std::string> { script.first, script.second.getTextScript() });

	return scripts;
}

void    GamesManager::setListener(GamesManager::OnGamesManagerEvent *listener) {
    mListener = listener;
}
