#ifndef GAME_HPP
#define GAME_HPP

#include <thread>

#include "../../components/screen/screen.hpp"

#include "board/board.hpp"

#include "../../enum/TextColors.hpp"

namespace lso {

    class Game {
        private:

            class Turn {
                private:

                    //...

                protected:

                    Game & game;

                public:

                    inline void changeTurnTo(Turn * turn) { game.changeTurnTo(std::move(turn)); };
            
                    virtual void makeMove(Board & board, const unsigned int column) const = 0;

                    virtual unsigned int takeInput() const = 0;

                public:

                    Turn(Game & game) : game(game) {}

                    Turn(const Turn &) = delete;
                    Turn(Turn &&) noexcept = delete;

                    virtual ~Turn() = default;

                    Turn &operator = (const Turn &) = delete;
                    Turn &operator = (Turn &&) noexcept = delete;

                    bool operator == (const Turn &) const noexcept = delete;
                    bool operator != (const Turn &) const noexcept = delete;
            };

            class PlayerTurn: public Turn {
                private:

                    //...

                protected:

                    //...

                public:

                    using Turn::Turn;

                    ~PlayerTurn() = default;

                    void makeMove(Board & board, const unsigned int column) const;

                    unsigned int takeInput() const;
            };

            class EnemyTurn: public Turn {
                private:

                    //...

                protected:

                    //...

                public:

                    using Turn::Turn;

                    ~EnemyTurn() = default;

                    void makeMove(Board & board, const unsigned int column) const;

                    unsigned int takeInput() const;
            };

        private:

            Board board;
            
            std::string playerName = "Player";
            std::string enemyName = "Enemy";
            
            TextColor playerColor;
            TextColor enemyColor;
            
            Turn * turn;

            void playTurn();

            unsigned int takeInput() const { return turn -> takeInput(); };
            
            inline bool validMove(const unsigned int column);
            
            inline void makeMove(const unsigned int column) { turn -> makeMove(board, column); };
            
            void changeTurnTo(Turn * turn);
            
            void print() const;

        protected:
            
            //...
            
        public:
            
            Game(const bool owner);

            void start();

            inline void reset() { board = Board(); };

        public:

            Game(const Game &) = delete;
            Game(Game &&) noexcept = default;

            ~Game() { delete turn; };

            Game &operator = (const Game &) = delete;
            Game &operator = (Game &&) noexcept = default;

            bool operator == (const Game &) const noexcept = delete;
            bool operator != (const Game &) const noexcept = delete;        
    };
    
}

#endif
