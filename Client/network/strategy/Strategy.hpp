#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>

#include "../shared/protocol.h"

namespace lso {

    template <typename Data>
    class Strategy {
        private:

            // ...

        protected:

            // ...

        public:

            virtual Data convertToHost(const std::vector<uint32_t> &) const = 0;
            virtual std::vector<uint32_t> convertToNetwork(const Data &) const = 0;

        public:

            Strategy() = default;
            Strategy(const Strategy &) = delete;
            Strategy(Strategy &&) = delete;

            virtual ~Strategy() = default;

            Strategy & operator = (const Strategy &) = delete;
            Strategy & operator = (Strategy &&) = delete;

            bool operator == (const Strategy &) const noexcept = delete;
            bool operator != (const Strategy &) const noexcept = delete;

    };

    class BoardStrategy: public Strategy<Board> {
        private:

            // ...

        protected:

            // ...

        public:

            Board convertToHost(const std::vector<uint32_t> &) const override;
            inline std::vector<uint32_t> convertToNetwork(const Board &) const override { throw std::runtime_error("Not implemented"); };

        public:

            using Strategy::Strategy;

    };

    class GameStrategy: public Strategy<Game> {
        private:

            // ...

        protected:

            // ...

        public:

            Game convertToHost(const std::vector<uint32_t> &) const override;
            inline std::vector<uint32_t> convertToNetwork(const Game &) const override { throw std::runtime_error("Not implemented"); };

        public:

            using Strategy::Strategy;

    };

    class GameListStrategy: public Strategy<std::vector<Game>> {
        private:

            // ...

        protected:

            // ...

        public:

            std::vector<Game> convertToHost(const std::vector<uint32_t> &) const override;
            inline std::vector<uint32_t> convertToNetwork(const std::vector<Game> &) const override { throw std::runtime_error("Not implemented"); };

        public:

            using Strategy::Strategy;
    };

    class StringStrategy: public Strategy<std::string> {
        private:

            // ...

        protected:

            // ...

        public:

            std::string convertToHost(const std::vector<uint32_t> &) const override;
            std::vector<uint32_t> convertToNetwork(const std::string &) const override { throw std::runtime_error("Not implemented"); };

        public:

            using Strategy::Strategy;
        
    };

    class UnsignedIntStrategy: public Strategy<unsigned int> {
        private:

            // ...

        protected:

            // ...

        public:

            unsigned int convertToHost(const std::vector<uint32_t> &) const override;
            std::vector<uint32_t> convertToNetwork(const unsigned int &) const override;

        public:

            using Strategy::Strategy;

    };

}

#endif
