#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <memory>
#include <algorithm>
#include <mutex>
#include <thread>

#include <ncurses.h>

#include "../board/GameBoard.hpp"
#include "../queue/Queue.hpp"
#include "../window/Window.hpp"

#include "../../enum/menu/MenuOption.hpp"

#include "../../model/lobby/Lobby.hpp"
#include "../../model/message/Message.hpp"

#include "../../network/strategy/Strategy.hpp"
#include "../../network/tcp/TCPClient.hpp"

namespace lso {

    class Client {

        private:

            class State {
                private:

                    // ...
                
                protected:
                
                    Client & context;
                    
                    std::unique_ptr<OutputWindow> outputWindow;
                    std::unique_ptr<InputWindow> inputWindow;

                public:

                    virtual void print() const = 0;

                    virtual void handleUserInput() = 0;

                    virtual void handleServerEvents(const Message & message);

                public:

                    State(Client & client);
                    State(const State &) = delete;
                    State(State &&) = delete;

                    virtual ~State() = default;

                    State &operator = (const State &) = delete;
                    State &operator = (State &&) = delete;

                    bool operator == (const Client &) const noexcept = delete;
                    bool operator != (const Client &) const noexcept = delete;
                
            };

            class LoginState: public State {
                private:

                    // ...

                protected:

                    // ...

                public:

                    LoginState(Client & client);

                    inline void print() const override;

                    void handleUserInput() override;

            };

            class MenuState: public State {
                private:

                    // ...

                protected:

                    // ...

                public:

                    MenuState(Client & context);

                    void print() const override;

                    void handleUserInput() override;
                
            };

            class LobbyState: public State {
                private:

                    Lobby lobby;
                    
                    std::string joinRequest;

                protected:

                    // ...

                public:

                    LobbyState(Client & context, Game game);

                    void print() const override;

                    void handleUserInput() override;

                    void handleServerEvents(const Message & message) override;
            };

            class InGameState: public State {
                private:

                    GameBoard board;
                    const bool owner;

                    std::string notification;

                protected:

                    // ...

                public:

                    InGameState(Client & context, const bool owner);

                    void print() const override;

                    void handleUserInput() override;
                    
                    void handleServerEvents(const Message & message) override;
            };

            class GameListState: public State {
                private:

                    std::vector<Lobby> lobbyList;
                    std::string notification;

                    inline std::string getNotification() const { return notification.empty() ? std::string("Nessuna nuova notifica") : notification; };
                    std::string getLobbyList() const;

                    void updateLobby(const Lobby &);
                    void removeLobby(const unsigned int);

                protected:

                    // ...

                public:

                    GameListState(Client & context, std::vector<Game> & gameList);

                    void print() const override;

                    void handleUserInput() override;

                    void handleServerEvents(const Message & message) override;
            };

        private:

            bool isRunning;

            std::unique_ptr<State> state;
            std::unique_ptr<TCPClient> serverConnection;

            std::thread senderThread;
            std::thread eventHandlerThread;
            std::thread receiverThread;

            Queue<Message> sendQueue;
            Queue<Message> receiveQueue;
            Queue<Message> eventQueue;

            std::mutex stateTransition;

        private:

            void startThreads();

            void handleEventLoop();
            void sendLoop();
            void receiveLoop();
            
            void transitionTo(std::unique_ptr<State>);

            inline void send(const Message & message) { sendQueue.Enqueue(message); };
            Message receive();

            void stop();

        protected:

            // ...

        public:

            void run();

        public:

            Client() : serverConnection(std::make_unique<TCPClient>()) { initscr(); };
            Client(const Client &) = delete;
            Client(Client &&) = delete;

            ~Client() { endwin(); };

            Client &operator = (const Client &) = delete;
            Client &operator = (Client &&) = delete;

            bool operator == (const Client &) const noexcept = delete;
            bool operator != (const Client &) const noexcept = delete;

    };

}

#endif
