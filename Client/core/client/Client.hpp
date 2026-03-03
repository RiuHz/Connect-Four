#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <memory>

#include "../../model/message/Message.hpp"

namespace lso {

    class Client {

        private:

            class State {
                private:

                    const Client & context;

                protected:

                    // ...

                public:

                    /* 
                        Facciamo la stampa in base al tipo di stato in cui ci troviamo:
                            Menu: stampo il menu iniziale aspettando una richiesta
                            Partita: Invio richiesta creazione partita, bla bla bla
                            Lobby: Tutto ciò dedicato alla partita in corso
                            Lista: Invio richiesta partite globali, bla bla bla
                    */

                    virtual void print() const = 0;

                    virtual void handleUserInput(const std::string & input) const = 0;

                    virtual void handleNetworkEvents(Message message) const = 0;

                public:

                    State(const Client & client) : context(client) {};
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

                    using State::State(const Client &); // Come va sistemata sta cosa del costruttore?

                    virtual void print() const;

                    virtual void handleUserInput(const std::string & input) const;

                    virtual void handleNetworkEvents(Message message) const;

            };

            class MenuState: public State {

            };

            class LobbyState: public State {

            };

            class InGameState: public State {
                // board come attr
            };

            class GameListState: public State {

            };

        private:

            std::unique_ptr<State> state;
    
            /*
                pointer tcp
                nome (?)
            */

        private:

            void transitionTo(std::unique_ptr<State> nextState) { state = std::move(nextState); };

        protected:

            // ...

        public:

            void run() const;

        public:

            Client() = default;
            Client(const Client &) = delete;
            Client(Client &&) = delete;

            ~Client() = default;

            Client &operator = (const Client &) = delete;
            Client &operator = (Client &&) = delete;

            bool operator == (const Client &) const noexcept = delete;
            bool operator != (const Client &) const noexcept = delete;

    };

}

#endif
