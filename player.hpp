// Define a class of type player
class Player {
        int current_score; // Min -95, max +95
    protected:
        std::vector<std::string> hand_v;
    public:
        std::string name;
        std::vector<std::string> table_hand_v;
        int cards_left = 7; //Max 7, min 0
        void initialise_hands_v();
        void view_hand_v();
        void pick_up_v(Two_decks& decks, std::string pile);
        void put_down_v(std::vector <std::string> put_down_cards);
        bool check_in_hand(std::string card);
        void increment_score(int num) {
            current_score += num;
        }
        void discard_v(Two_decks& decks, std::string card);
        std::vector<std::vector<std::string>> get_score(std::vector<std::vector<std::string>>& scores);
        void set_hand();
        Player* next;
};
