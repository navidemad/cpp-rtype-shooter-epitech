#include "GamesManager.hpp"
#include "GameException.hpp"
#include "GamesManagerException.hpp"
#include "GameProperties.hpp"
#include "PortabilityBuilder.hpp"
#include "ScopedLock.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

/*
-------------------  scoped functions --------------------------
*/

std::vector<std::shared_ptr<NGame::Game>>& GamesManager::getGames(void) {
    Scopedlock(mMutex);

    return mGames;
}

const ScriptLoader& GamesManager::getScriptLoader(void) const {
    Scopedlock(mMutex);

    return mScriptLoader;
} 

PlayerCommunicationManager& GamesManager::getPlayerCommunicationManager(void) {
    Scopedlock(mMutex);

    return mPlayerCommunicationManager;
}

GamesManager::OnGamesManagerEvent* GamesManager::getListener(void) const {
    Scopedlock(mMutex);

    return mListener;
}

void    GamesManager::setListener(GamesManager::OnGamesManagerEvent *listener) {
    Scopedlock(mMutex);

    mListener = listener;
}

void GamesManager::addGameToList(const std::shared_ptr<NGame::Game>& game) {
    Scopedlock(mMutex);

    mGames.push_back(game);
}

std::vector<std::shared_ptr<NGame::Game>>::iterator GamesManager::removeItGameFromList(std::vector<std::shared_ptr<NGame::Game>>::iterator it_game) {
    Scopedlock(mMutex);

    return mGames.erase(it_game);
}



/*
------------------- OTHERS --------------------------
*/
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
        games = getGames();
		for (auto it = games.begin(); it != games.end();)
		{
            if ((*it)->getPullEnded() == true)
            {
        		switch ((*it)->getState())
        		{
            		case NGame::Game::State::RUNNING:
                        (*it)->setPullEnded(false);
        				*mThreadPool << std::bind(&NGame::Game::pull, (*it));
                        ++it;
            			break;
            		case NGame::Game::State::DONE:
            			it = terminatedGame(findGameByName((*it)->getProperties().getName()));
            			break;
                    default:
                        ++it;
                        break;
        		}
            }
            else
            {
                ++it;
            }
		}
    }
}

void GamesManager::createGame(const NGame::Properties& properties, const Peer &peer) {
	if (findGameByName(properties.getName()) != getGames().end())
		throw GamesManagerException("Game name already taken", ErrorStatus(ErrorStatus::Error::KO));
	if (properties.getMaxPlayers() < 1 || properties.getMaxPlayers() > 4)
		throw GamesManagerException("Invalid max nb players", ErrorStatus(ErrorStatus::Error::KO));
	if (properties.getMaxSpectators() < 0 || properties.getMaxSpectators() > 4)
		throw GamesManagerException("Invalid max nb observers", ErrorStatus(ErrorStatus::Error::KO));
	if (getScriptLoader().isExist(properties.getLevelName()) == false)
		throw GamesManagerException("Invalid level name", ErrorStatus(ErrorStatus::Error::KO));
	auto game = std::make_shared<NGame::Game>(properties, getScriptLoader().getScript(properties.getLevelName()));

    game->setListener(this);
    game->setOwner(peer);

    addGameToList(game);
}

void GamesManager::removeGame(const Peer &peer, const std::string& name) {
    auto game = findGameByName(name);

    if (game == getGames().end())
        throw GamesManagerException("Try to delete an undefined game", ErrorStatus(ErrorStatus::Error::KO));

	if (peer == (*game)->getOwner()) {
		removeClientsFromWhitelist(*game);
        removeItGameFromList(game);
	}
    else
        throw GamesManagerException("You can remove a game only if you are owner", ErrorStatus(ErrorStatus::Error::KO));
}

void GamesManager::joinGame(NGame::USER_TYPE typeUser, const Peer &peer, const std::string &name, const std::string &pseudo) {
    auto it_game = findGameByHost(peer);
    auto it_end = getGames().end();

    if (it_game != it_end)
        throw GamesManagerException("User is already in a game", ErrorStatus(ErrorStatus::Error::KO));

    auto game = findGameByName(name);
    if (game == getGames().end())
        throw GamesManagerException("Try to join an undefined game party name", ErrorStatus(ErrorStatus::Error::KO));

    (*game)->addUser(typeUser, peer, pseudo);
}

void GamesManager::playGame(const Peer &peer, const std::string &name, const std::string &pseudo) {
    try {
        joinGame(NGame::USER_TYPE::PLAYER, peer, name, pseudo);
        getPlayerCommunicationManager().addPeerToWhiteList(peer);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::spectateGame(const Peer &peer, const std::string &name) {
    try {
        joinGame(NGame::USER_TYPE::SPECTATOR, peer, name);
        getPlayerCommunicationManager().removePeerFromWhiteList(peer);
    }
    catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::leaveGame(const Peer &peer) {
    try {
        auto game = findGameByHost(peer);

        if (game == getGames().end())
            throw GamesManagerException("Try to leave a player who isn't in a game", ErrorStatus(ErrorStatus::Error::KO));

        (*game)->delUser(peer);
        getPlayerCommunicationManager().removePeerFromWhiteList(peer);
    } catch (const GameException& e) {
        throw GamesManagerException(e.what(), ErrorStatus(ErrorStatus::Error::KO));
    }
}

void GamesManager::updatePseudo(const Peer &peer, const std::string &pseudo) {
    auto game = findGameByHost(peer);

    if (game == getGames().end())
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

/*
** PlayerCommunicationManager::OnPlayerCommunicationManagerEvent
*/ 
void GamesManager::onPlayerFire(const Peer &peer) {
    try {
        auto game = findGameByHost(peer);

        if (game == getGames().end())
            throw GamesManagerException("Try to fire a player that is not in a game", ErrorStatus(ErrorStatus::Error::KO));
        
        try {
            auto component = (*game)->fire(peer);
            for (const auto &user : (*game)->getUsers())
                getPlayerCommunicationManager().sendMoveResource(user.getPeer(), component.getId(), component.getType(), component.getX(), component.getY(), component.getAngle());
        }
        catch (const GameException& e) {
            std::cerr << "GameException caught: " << e.what() << std::endl;
        }
    }
    catch (const GamesManagerException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GamesManager::onPlayerMove(IResource::Direction direction, const Peer &peer) {
    try {
        auto game = findGameByHost(peer);

        if (game == getGames().end())
            throw GamesManagerException("Try to move a player that is not in a game", ErrorStatus(ErrorStatus::Error::KO));

        try {
            auto component = (*game)->move(peer, direction);
            for (const auto &user : (*game)->getUsers())
                getPlayerCommunicationManager().sendMoveResource(user.getPeer(), component.getId(), component.getType(), component.getX(), component.getY(), component.getAngle());
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
    std::list<Peer> gameUsers;

    for (const auto &user : (*it)->getUsers()) {
        onNotifyUserGainScore(user.getPeer(), user.getId(), user.getPseudo(), user.getScore());
        gameUsers.push_back(user.getPeer());
    }

    auto listener = getListener();
    if (listener)
        listener->onEndGame((*it)->getProperties().getName(), gameUsers);

    removeClientsFromWhitelist(*it);
    return removeItGameFromList(it);
}

void GamesManager::onRemovePeerFromWhiteList(const Peer& peer) {
    getPlayerCommunicationManager().removePeerFromWhiteList(peer);
}

void GamesManager::onNotifyUsersComponentRemoved(const std::vector<NGame::User>& users, uint64_t id) {
    for (const auto &user : users)
        getPlayerCommunicationManager().sendDestroyResource(user.getPeer(), id);
}

void GamesManager::onNotifyUsersComponentAdded(const std::vector<NGame::User>& users, const NGame::Component& component) {
    for (const auto &user : users)
        getPlayerCommunicationManager().sendMoveResource(user.getPeer(), component.getId(), component.getType(), component.getX(), component.getY(), component.getAngle());
}

void GamesManager::onNotifyUserGainScore(const Peer &peer, uint64_t id, const std::string &pseudo, uint64_t score) {
    getPlayerCommunicationManager().sendUpdateScore(peer, id, pseudo, score);
}

void GamesManager::onNotifyTimeElapsedPing(const Peer &peer, double elapsedPing) {
    getPlayerCommunicationManager().sendTimeElapsedPing(peer, elapsedPing);
}

void    GamesManager::removeClientsFromWhitelist(const std::shared_ptr<NGame::Game> &game) {
    auto usersInGame = game->getUsers();
    std::for_each(usersInGame.begin(), usersInGame.end(), [&](const NGame::User& user) {
        getPlayerCommunicationManager().removePeerFromWhiteList(user.getPeer());
    });
}

const NGame::Properties &GamesManager::getGameProperties(const std::string &name) {
    auto game = findGameByName(name);

    if (game == getGames().end())
        throw GamesManagerException("Try to get properties of an undefined game", ErrorStatus(ErrorStatus::Error::KO));

    return (*game)->getProperties();
}

std::list<NGame::Properties> GamesManager::getGamesProperties(void) {
	std::list<NGame::Properties> gamesProperties;

    for (const auto& game : getGames())
        gamesProperties.push_back(game->getProperties());

    return gamesProperties;
}

std::vector<std::shared_ptr<NGame::Game>>::iterator GamesManager::findGameByName(const std::string& name) {
    auto it = getGames().begin();
    while (it != getGames().end())
    {
        if ((*it)->getProperties().getName() == name)
            return it;
        ++it;
    }
    return it;
}

std::vector<std::shared_ptr<NGame::Game>>::iterator GamesManager::findGameByHost(const Peer &peer) {
    auto it = getGames().begin();
    while (it != getGames().end())
    {
        auto users = (*it)->getUsers();
        if (users.size() == 0)
        {
            for (const auto& user: users)
                if (user.getPeer() == peer)
                    return it;
        }
        ++it;
    }
    return it;
}

std::list<std::pair<std::string, std::string>> GamesManager::getScripts(void) const {
	std::list<std::pair<std::string, std::string>> scripts;

	for (const auto &script : getScriptLoader().getScripts())
		scripts.push_back(std::pair<std::string, std::string> { script.first, script.second.getTextScript() });

	return scripts;
}
