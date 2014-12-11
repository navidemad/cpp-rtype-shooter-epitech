#pragma once

class RTypeClient;
#include <QObject>
#include <vector>
#include <list>
#include <stdint.h>
#include "Entity.hpp"
#include "Component.hpp"
#include "../Core/System.hpp"
#include "ECSManager.hpp"
#include "Network/ServerCommunication.hpp"

class ECSManagerNetwork : public QObject, public ECSManager
{
	Q_OBJECT

	signals:
		void SignalCreateGame(const std::string &name, const std::string &levelName, int nbPlayer, int nbObserver);
        bool SignalDeleteGame(const std::string &name);
        bool SignalDiconect(void);
        bool SignalFire(void);
        bool SignalJoinGame(const std::string &name);
        bool SignalLeaveGame(void);
        bool SignalListGame(void);
        bool SignalListLevel(void);
        bool SignalMove(IResource::Direction direction);
        bool SignalObserveGame(const std::string &name);
        bool SignalShowGame(const std::string &name);
        bool SignalUpdatePseudo(const std::string &pseudo);
        void SignalSetServerIp(const std::string &ip);
        void SignalSetServerPortTcp(int port);
        bool SignalConnectToServer(void);

	public slots:
		void OnDestroyResource(int id);
		void OnEndGame(const std::string &name);
		void OnError(ICommand::Instruction instruction, ErrorStatus::Error);
		void OnMoveResource(IResource::Type type, float x, float y, short angle, int id);
		void OnShowGame(const std::string &name, const std::string &levelName, int nbPlayer, int maxPlayer, int nbObserver, int maxObserver);
		void OnShowLevel(const std::string &name, const std::string &script);
		void OnTimeElapse(int64_t time);
		void OnUpdateScore(const std::string &name, int id, int score);
        void OnCloseSocket(void);

	public:
		ECSManagerNetwork();

	private:
		void	createPlayer();
		void	createBullet();
		void	createEnnemy();
		void	createBonus();
};
