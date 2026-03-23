#ifndef LOBBY_HPP
#define LOBBY_HPP

#include <string>

namespace lso {

    class Lobby {
        private:

            unsigned int id;

            std::string owner;
            std::string opponent;

        protected:

            //...

        public:

            unsigned int getID() const noexcept { return id; };
            const std::string & getOwner() const noexcept { return owner; };
            const std::string getOpponent() const noexcept { return opponent.empty() ? "In attesa..." : opponent; };

        public:

            Lobby(Game game) : id(game.id), owner(game.proprietario), opponent(game.avversario) {};

            Lobby(const Lobby &) = default;
            Lobby(Lobby &&) = default;

            virtual ~Lobby() = default;

            Lobby & operator = (const Lobby &) = default;
            Lobby & operator = (Lobby &&) = default;

            bool operator == (const Lobby & other) const noexcept { return id == other.id; };
            bool operator != (const Lobby & other) const noexcept { return ! (*this == other); };

    };

}

#endif
