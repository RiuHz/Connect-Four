#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <memory>
#include <iostream>

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

                    virtual void print() const override;

                    virtual void handleUserInput(const std::string & input) const override;

                    virtual void handleNetworkEvents(Message message) const override;

            };

            class MenuState: public State {
                private:

                    // ...

                protected:

                    // ...

                public:

                    using State::State; // dovrebbe workare cosi?

                    virtual void print() const override;

                    virtual void handleUserInput(const std::string & input) const override;

                    virtual void handleNetworkEvents(Message message) const override;

            };

            class LobbyState: public State {
                private:

                    // ...

                protected:

                    // ...

                public:

                    using State::State; // dovrebbe workare cosi?

                    virtual void print() const override;

                    virtual void handleUserInput(const std::string & input) const override;

                    virtual void handleNetworkEvents(Message message) const override;

                    void onEnter() const; // dubbio dubbioso

            };

            class InGameState: public State {

                private:
                    // board come attr

                    // ...

                protected:

                    // ...

                public:

                    using State::State; // dovrebbe workare cosi?

                    virtual void print() const override;

                    virtual void handleUserInput(const std::string & input) const override;

                    virtual void handleNetworkEvents(Message message) const override;
            };

            class GameListState: public State {
                private:

                    // ...

                protected:

                    // ...

                public:

                    using State::State; // dovrebbe workare cosi?

                    virtual void print() const override;

                    virtual void handleUserInput(const std::string & input) const override;

                    virtual void handleNetworkEvents(Message message) const override;

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
