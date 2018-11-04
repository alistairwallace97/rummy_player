// Define a class for the two piles, the discard and blind
// piles.
class Two_decks {
        std::vector<std::string> blind_pile_v;
        std::vector<std::string> discard_pile_v;
    public:
        std::string discard_top;
        int total_cards;
        int total_cards_v;
        int current_num_blind;
        void initialise_decks_v(int num_decks, 
                              int num_players);
        void view_decks_v();        
        std::string remove_top_card_v(std::string pile);
        std::string add_to_discard_v(std::string card){
            discard_pile_v.push_back(card);
        }
        void check_flip_decks();
};
