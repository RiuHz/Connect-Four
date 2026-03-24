#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <memory>
#include <algorithm>
#include <mutex>
#include <thread>
#include <atomic>

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

                    using State::State;

                    inline void print() const override;

                    void handleUserInput() override;

            };

            class MenuState: public State {
                private:

                    // ...

                protected:

                    // ...

                public:

                    using State::State;

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

                    LobbyState(Client & context, Game game) : State(context), lobby(game) {};
                    LobbyState(Client & context, Lobby lobby) : State(context), lobby(lobby) {};

                    void print() const override;

                    void handleUserInput() override;

                    void handleServerEvents(const Message & message) override;
            };

            class InGameState: public State {
                private:

                    GameBoard board;
                    const bool owner;
                    
                    std::atomic<bool> nextTurn {true};
                    
                    std::unique_ptr<State> turnState;

                private:

                    void changeTurnTo(std::unique_ptr<State> state);

                private:

                    class TurnState: public State {
                        private:

                                InGameState & gameContext;

                            protected:

                                //...

                            public:

                                void print() const override;

                                void handleUserInput() override;

                                void handleServerEvents(const Message & message) override;

                            public:

                                TurnState(Client & clientContext, InGameState & gameContext) : State(clientContext), gameContext(gameContext) {};
                        };

                        class WaitingState: public State {
                            private:

                                InGameState & gameContext;

                                

                            protected:

                                //...

                            public:

                                void print() const override;

                                void handleUserInput() override;

                                void handleServerEvents(const Message & message) override;

                            public:

                                WaitingState(Client & clientContext, InGameState & gameContext) : State(clientContext), gameContext(gameContext) {};
                        };


                protected:

                    // ...

                public:

                    InGameState(Client & context, const bool owner);

                    inline void print() const override { turnState -> print(); };

                    void handleUserInput() override;
                    
                    inline void handleServerEvents(const Message & message) override { turnState -> handleServerEvents(message); };
            };

            class RematchState: public State {
                private:

                    const GameBoard & board;
                    const bool owner;

                    std::string notification;

                private:

                    void handleRematchResponse();

                protected:

                    // ...

                public:

                    RematchState(Client & context, const MessageType esito, const GameBoard & board, const bool owner);

                    void print() const override;

                    void handleUserInput() override;

            };

            class GameListState: public State {
                private:

                    std::vector<Lobby> lobbyList;
                    std::string notification;

                private:

                    inline std::string getNotification() const { return notification.empty() ? std::string("Nessuna nuova notifica") : notification; };
                    std::string getLobbyList() const;

                    Lobby findLobby(const unsigned int);
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

            std::recursive_mutex stateTransition;

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
