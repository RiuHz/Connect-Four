#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <memory>
#include <algorithm>

#include <ncurses.h>

#include "../board/GameBoard.hpp"
#include "../window/Window.hpp"

#include "../../enum/menu/MenuOption.hpp"

#include "../../model/message/Message.hpp"

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

                    virtual void handleUserInput() const = 0;

                    virtual void handleNetworkEvents(const Message & message) const = 0;

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

                    void handleUserInput() const override;

                    void handleNetworkEvents(const Message & message) const override;

            };

            class MenuState: public State {
                private:

                    // ...

                protected:

                    // ...

                public:

                    MenuState(Client & context);

                    void print() const override;

                    void handleUserInput() const override;

                    void handleNetworkEvents(const Message & message) const override;
            };

            class LobbyState: public State {
                private:

                    // ...
                    // Lobby

                protected:

                    // ...

                public:

                    LobbyState(Client & context);

                    void print() const override;

                    void handleUserInput() const override;

                    void handleNetworkEvents(const Message & message) const override;
            };

            class InGameState: public State {
                private:
                    // TODO
                    // *const Board & board;

                protected:

                    // ...

                public:

                    InGameState(Client & context);

                    void print() const override;

                    void handleUserInput() const override;
                    
                    void handleNetworkEvents(const Message & message) const override;
            };

            class GameListState: public State {
                private:

                    // ...
                    // Lobby List

                protected:

                    // ...

                public:

                    GameListState(Client & context);

                    void print() const override;

                    void handleUserInput() const override;

                    void handleNetworkEvents(const Message & message) const override;
            };

        private:

            std::unique_ptr<State> state;
            std::unique_ptr<TCPClient> serverConnection;

            bool isRunning;

        private:

            void setup();

            void transitionTo(std::unique_ptr<State> nextState) { state = std::move(nextState); };

        protected:

            // ...

        public:

            void run();

        public:

            Client() { initscr(); };
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
