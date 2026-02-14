#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../game.hpp"

#include "../../../enum/TextColors.hpp"

namespace lso {

    class State {
        private:

            //...

        protected:

            Game & game;

        public:
            
            inline void changeStateTo(std::unique_ptr<State> state) { game.changeStateTo(std::move(state)); };
            
            virtual void makeMove(Board & board, const unsigned int column) const = 0;
            
        public:
            
            State(Game & game) : game(game) {}

            State(const State &) = delete;
            State(State &&) noexcept = delete;

            virtual ~State() = default;

            State &operator = (const State &) = delete;
            State &operator = (State &&) noexcept = delete;

            bool operator == (const State &) const noexcept = delete;
            bool operator != (const State &) const noexcept = delete;
    };

    class MyTurnState: public State {
        private:

            //...

        protected:

            //...

        public:
            using State::State;

            void makeMove(Board & board, const unsigned int column) const;

    };

    class EnemyTurnState: public State {
        private:

            //...

        protected:

            //...

        public:
            using State::State;

            void makeMove(Board & board, const unsigned int column) const;

    };

}

#endif
