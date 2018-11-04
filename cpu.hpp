#include "player.hpp"

class Cpu: public Player {
    public:
        int value_card(std::string card, 
                        std::vector<std::string>& useful_cards,
                        int num_set);
        std::string which_pick(Two_decks decks);
        std::vector<std::string> check_put_down();
        std::string which_throw();
};
