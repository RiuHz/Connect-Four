#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <memory>
#include <iostream>

#include "../../components/screen/Screen.hpp"

#include "../board/Board.hpp"

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

                public:

                    virtual void print() const = 0;

                    virtual void handleUserInput(const std::string & input) const = 0;

                    virtual void handleNetworkEvents(const Message & message) const = 0;

                public:

                    State(Client & client) : context(client) {};
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

                    void print() const override;

                    void handleUserInput(const std::string & input) const override;

                    void handleNetworkEvents(const Message & message) const override;

            };

            class MenuState: public State {
                private:

                    // ...

                protected:

                    // ...

                public:

                    using State::State;

                    void print() const override;

                    void handleUserInput(const std::string & input) const override;

                    void handleNetworkEvents(const Message & message) const override;
            };

            class LobbyState: public State {
                private:

                    // ...
                    // Lobby

                protected:

                    // ...

                public:

                    using State::State;

                    void print() const override;

                    void handleUserInput(const std::string & input) const override;

                    void handleNetworkEvents(const Message & message) const override;
            };

            class InGameState: public State {
                private:
                
                    const Board & board;

                protected:

                    // ...

                public:

                    using State::State;

                    void print() const override;

                    void handleUserInput(const std::string & input) const override;
                    
                    void handleNetworkEvents(const Message & message) const override;
            };

            class GameListState: public State {
                private:

                    // ...
                    // Lobby List

                protected:

                    // ...

                public:

                    using State::State;

                    void print() const override;

                    void handleUserInput(const std::string & input) const override;

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

            Client() { Screen::open(); };
            Client(const Client &) = delete;
            Client(Client &&) = delete;

            ~Client() { Screen::close(); };

            Client &operator = (const Client &) = delete;
            Client &operator = (Client &&) = delete;

            bool operator == (const Client &) const noexcept = delete;
            bool operator != (const Client &) const noexcept = delete;

    };

}

#endif
