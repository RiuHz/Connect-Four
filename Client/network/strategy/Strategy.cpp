#include "Strategy.hpp"

Board lso::BoardStrategy::convertToHost(const std::vector<uint32_t> & payload) const {
    Board board;

    memcpy(board.grid, payload.data(), sizeof(board.grid));

    return board;
};

Game lso::GameStrategy::convertToHost(const std::vector<uint32_t> & payload) const {
    Game game;
    unsigned int offset = 0;

    game.id = payload[offset++];

    memcpy(game.proprietario, & payload[offset], NAME_LEN);
    offset += (NAME_LEN + 3) / 4;

    memcpy(game.avversario, & payload[offset], NAME_LEN);
    offset += (NAME_LEN + 3) / 4;

    return game;
};

std::vector<Game> lso::GameListStrategy::convertToHost(const std::vector<uint32_t> & payload) const {
    std::vector<Game> gameList;

    unsigned int totalBytes = payload.size();
    unsigned int offset = 0;

    while (offset < totalBytes) {
        Game game;

        game.id = payload[offset++];

        memcpy(game.proprietario, & payload[offset], NAME_LEN);
        offset += (NAME_LEN + 3) / 4;

        memcpy(game.avversario, & payload[offset], NAME_LEN);
        offset += (NAME_LEN + 3) / 4;

        gameList.push_back(game);
    }

    return gameList;
}

std::string lso::StringStrategy::convertToHost(const std::vector<uint32_t> & payload) const {
    std::string string = (char *) payload.data();

    return string;
}

unsigned int lso::UnsignedIntStrategy::convertToHost(const std::vector<uint32_t> & payload) const {
    return payload[0];
};

std::vector<uint32_t> lso::UnsignedIntStrategy::convertToNetwork(const unsigned int & number) const {
    std::vector<uint32_t> payload;

    payload.push_back(number);

    return payload;
};
