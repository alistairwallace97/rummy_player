// A program for playing the card game rummy. 
// Stores the players in a linked list of items of type
// player. In the main it will set up all the necessary
// variables, then iterate around a circular linked list
// until the exit condition is met. (One of the players 
// is out)

// Things to do
//  - Write a value_card() function
//  - Write a function for deciding which card to pick on
//    the first run through the pack
//  - Write a function for deciding which card to pick on
//    the second run through the pack.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

// Define a class for the two piles, the discard and blind
// piles.
class two_decks {
        vector<string> blind_pile_v;
        vector<string> discard_pile_v;
    public:
        string discard_top;
        int total_cards;
        int total_cards_v;
        int current_num_blind;
        void initialise_decks_v(int num_decks, 
                              int num_players);
        void view_decks_v();        
        string remove_top_card_v(string pile);
        string add_to_discard_v(string card){
            discard_pile_v.push_back(card);
        }
        void check_flip_decks();
};

// Define a class of type player
class player {
        int current_score; // Min -95, max +95
    protected:
        vector<string> hand_v;
    public:
        string name;
        string* table_hand; // Max length 7
        vector<string> table_hand_v;
        int cards_left = 7; //Max 7, min 0
        void initialise_hands_v();
        void view_hand_v();
        void pick_up_v(two_decks& decks, string pile);
        void put_down_v(vector <string> put_down_cards);
        bool check_in_hand(string card);
        void increment_score(int num) {
            current_score += num;
        }
        void discard_v(two_decks& decks, string card);
        vector<vector<string>> get_score(vector<vector<string>>& scores);
        void set_hand();
        player* next;
};

typedef player* plist;

class cpu: public player {
    public:
        int value_card(string card, 
                        vector<string>& useful_cards,
                        int num_set);
        string which_pick(two_decks decks);
        vector<string> check_put_down();
        string which_throw();
};

// Function Declarations
plist reverse_list(plist in_lst);
void print_lst(plist in_lst);
plist loop_list(plist in_lst);
string all_but_last(string str);
bool are_aces_high(const vector <string>& put_down_cards);
bool check_valid_set(vector <string>& put_down_cards);
int eval_card(const string& str, bool aces_high);
void get_scores(int num_players,
                vector<vector<string>>& scores,
                plist looped_list);
string check_pair(string card1, string card2);
void update_vector_value(vector<string>& relations);
void check_adds_to_set(string& current_set, string card);
string val_to_string(int card_val);
string last_char_as_string(string str);


void two_decks::initialise_decks_v(int num_decks, 
                                 int num_players){
    total_cards = (52*num_decks) - (7*num_players);
    current_num_blind = total_cards -1;
    for(int i=0; i<current_num_blind; i++){
        blind_pile_v.push_back("unk");
    }
    cout << "What is the first card on the discard pile?\n";
    cin >> discard_top;
    discard_pile_v.push_back(discard_top);
}

void two_decks::view_decks_v(){
    cout << "\nThe current decks\nblind: ";
    cout << blind_pile_v.size() << endl;
    for(int i=0; i<blind_pile_v.size(); i++){
        cout << blind_pile_v[i] << ", ";
    }
    cout << "\ndiscard: ";
    cout << discard_pile_v.size() << endl;
    for(int i=0; i<discard_pile_v.size(); i++){
        cout << discard_pile_v[i] << ", ";
    }
    cout << endl;
}

string two_decks::remove_top_card_v(string pile){
    string top_card;
    if(pile == "b"){
        // Pop_front
        top_card = blind_pile_v.front();
        blind_pile_v.erase(blind_pile_v.begin());
    }
    else if(pile == "d"){
        top_card = discard_pile_v.back();
        discard_pile_v.pop_back();
    }
    else{
        cout << "Error: two_decks::remove_top_card_v - pile \
        input (" << pile << ") was not in the right \
        input.\nShould be either 'b' or 'd'.";
        top_card = "Error";
    }
    return top_card;
}

void two_decks::check_flip_decks(){
    if(blind_pile_v.size() == 0){
        reverse(discard_pile_v.begin(), discard_pile_v.end());
        blind_pile_v = discard_pile_v;
        discard_pile_v.clear();
        cout << "Flipped decks" << endl;
    }
}

void player::initialise_hands_v(){
    for(int i=0; i<7; i++){
        hand_v.push_back("unk");
    }
}

void player::view_hand_v(){
    cout << "\nname: " << name;
    cout << "\nhand: ";
    for(int i=0; i<hand_v.size(); i++){
        cout << hand_v[i] << ", ";
    }
    cout << "\ntable_hand: ";
    for(int i=0; i<7-cards_left; i++){
        cout << table_hand_v[i] << ", ";
    }
    cout << endl;    
}

void player::pick_up_v(two_decks& decks, string pile){
    if((pile == "b")||(pile == "d")){
        string test_var = decks.remove_top_card_v(pile);
        hand_v.push_back(test_var);
    }
    else{
        cout << "Error: player::pick_up_v - pile input (" <<
        pile << ") was not in the right input.\nShould be \
        either 'b' or 'd'." << endl;
    }
}

void player::put_down_v(vector <string> put_down_cards){
    bool all_in=true, aces_high=true;
    string tmp;
    cout << endl;
    // Check that all the cards are in the players hand
    for(int i=0; i<put_down_cards.size(); i++){
        all_in = all_in&&check_in_hand(put_down_cards[i]);
    }
    // Check that they are a valid set
    if(all_in && check_valid_set(put_down_cards)){
        // For Later 
        //     Check they aren't in the decks or anyone 
        //     else's hand
        for(int i=0; i<put_down_cards.size(); i++){
            // add to table hand
            table_hand_v.push_back(put_down_cards[i]); 
            // increment current score
            tmp = put_down_cards[i];
            aces_high = are_aces_high(put_down_cards);
            increment_score(eval_card(tmp, aces_high));
            // remove from hand
            hand_v.erase(remove(hand_v.begin(), hand_v.end(), put_down_cards[i]), hand_v.end());
            // decrement cards_left
            cards_left -= 1;
        }
    }
    else{
        if(!all_in){
            cout << "Error: put_down_v - not all of these\
            cards were in the players hand" << endl;
        }
        if(!check_valid_set(put_down_cards)){
            cout << "Error: put_down_v - These cards were\
            not a valid set" << endl;
        }
    }
}

bool player::check_in_hand(string card){
    bool found = false;
    // Check if the card is known to be in the hand
    for(int i=0; (i<hand_v.size())&&(!found); i++){
        if(card == hand_v[i]){
            found = true;
        }
    }
    // If not say one of the unknown cards must have been
    // that card
    if(!found){
        for(int i=0; (i<hand_v.size())&&(!found); i++){
            if(hand_v[i] == "unk"){
                hand_v[i] = card;
                found = true;
            }
        }
    }
    return found;
}

void player::discard_v(two_decks& decks, string card){
    // Check the card is in the player's hand
    if(check_in_hand(card)){
        // Add it to the top of the discard pile
        decks.add_to_discard_v(card);
        // Update the discard_top variable
        decks.discard_top = card;
        // Remove it from the players hand
        hand_v.erase(remove(hand_v.begin(), hand_v.end(), card), hand_v.end());
    }
    else{
        cout << "Error: discard_v - the card (" << card <<
        ") is not in this player's hand" << endl;
    }
}

vector<vector<string>> player::get_score(vector<vector<string>>& scores){
    // Initialisation
    bool all_known = true;
    int num_unknown = 0;
    string tmp_card;
    // Printing the player's ending hand
    cout << name << "'s ending hand:\n";
    for(int i=0; i<cards_left; i++){
        cout << hand_v[i] <<", ";
        if(hand_v[i] == "unk"){
            all_known = false;
            num_unknown += 1;
        }
    }
    cout << endl;
    if(!all_known){
        for(int i=0; i<cards_left; i++){
            cout << hand_v[i] <<", ";
            if(hand_v[i] == "unk"){
                cout << "\ni = " << i << endl;
                cout << "Please input what this card was:" << endl;
                cin >> tmp_card;
                hand_v[i] = tmp_card;
                cout << "\nThanks\n";
            }
        }
    }
    for(int j=0; j<cards_left; j++){
        // Subtract the value of the card from current_score 
        current_score -= eval_card(hand_v[0], true);
        // Remove that card from the hand
        hand_v.erase(remove(hand_v.begin(), hand_v.end(), hand_v[0]), hand_v.end());
    }
    hand_v.clear();
    // Add [name, current_score] to scores
    vector<string> name_and_score;
    name_and_score.push_back(name);
    name_and_score.push_back(to_string(current_score));
    scores.push_back(name_and_score);
    return scores;
}

void player::set_hand(){
    // For debuging
    string yes_or_no;
    // Print the current hand
    cout << "In set hand\n" << name << "'s current hand is:\n";
    for(int i=0; i<cards_left; i++){
        cout << hand_v[i] << ", ";     
    }
    cout << endl;
    // Ask if they want to change anything
    cout << "Do you want to change the hand? (y or n)" << endl;
    cin >> yes_or_no;
    if(yes_or_no == "y"){
        for(int i=0; i<cards_left; i++){
            cout << "\ni = " << i << ", hand_v[i] = " << hand_v[i] << endl;
            cout << "Change this? (n or the card you want it to be, eg 5h):\n";
            cin >> yes_or_no;
            if(yes_or_no != "n"){
                hand_v[i] = yes_or_no;
            }
        }
        cout << endl;
    }
    // Print the end hand
    cout << name << "'s final hand is:\n";
    for(int i=0; i<cards_left; i++){
        cout << hand_v[i] << ", ";   
    }
    cout << endl;
}

// vector el = n-slh or n-ns, eg 3-a35 or 2-5hc
int cpu::value_card(string card,
                    vector<string>& useful_cards,
                    int num_set){
    // if(n<=2) (vector should just be {"value:0"})
    //  set vector to empty
    //  set n = 2
    //  for each other card, check if they make a pair
    //   if(pair)
    //    add to list
    //    update value
    //  if(vec.size > 1)
    //   call recursively on the list with n = 3
    
    // If(n>2 and n<5)  (for now)
    //  For a highest group in list
    //   Check if there are any extra connected to this
    //   group
    //   If(extra)
    //    Replace root group with extra group 
    //    update value
    //  If(any extras)
    //   call recursively with n = n+1

    // If(n>4)
    //  Do nothing
    // Else return error "n needs to start at 2"
}

string check_pair(string card1, string card2){
    // Return in form:
    // 2-h4-5 or 2-5hc or 2-st-j or "" if nothing
    // Checks if any two cards are related
    bool pair = false;
    string ret_string = "", card_type;
    // If same type of card they're a pair, eg 5h & 5d
    if((all_but_last(card1) == all_but_last(card2))
        && (card1 != card2)){
        pair = true;
        if(all_but_last(card1) == "10"){
            card_type = "t";
        }
        else{
            card_type = all_but_last(card1);
        }
        ret_string = "2-" + card_type + card1.back() 
                        + card2.back();
    }
    // If(same suit), eg 5h & 6h
    else if(card1.back() == card2.back()){
        // and If consecutive 
        int card1_val_high = abs(eval_card(card1, true));
        int card2_val_high = abs(eval_card(card2, true));
        int card1_val_low = abs(eval_card(card1, false));
        int card2_val_low = abs(eval_card(card2, false));
        int diff_high = abs(card1_val_high - card2_val_high);
        int diff_low = abs(card1_val_low - card2_val_low);
        if(diff_high == 1){
            pair = true;
            if(card1_val_high > card2_val_high){
                ret_string = "2-" + last_char_as_string(card1)
                            + val_to_string(card2_val_high) + "-"
                            + val_to_string(card1_val_high);
            }
            else{
                ret_string = "2-" + last_char_as_string(card1)
                            + val_to_string(card1_val_high) + "-"
                            + val_to_string(card2_val_high);
            }
        }
        else if(diff_low == 1){
            pair = true;
            if(card1_val_low > card2_val_low){
                ret_string = "2-" + last_char_as_string(card1)
                            + val_to_string(card2_val_low) + "-"
                            + val_to_string(card1_val_low);
            }
            else{
                ret_string = "2-" + last_char_as_string(card1)
                            + val_to_string(card1_val_low) + "-"
                            + val_to_string(card2_val_low);
            }
        }
    } 
    return ret_string;
}

string last_char_as_string(string str){
    return str.substr(str.length()-1,1);
}

void update_vector_value(vector<string>& relations){
    int value = 0;
    string value_str;
    for(int i=0; i<relations.size()-1; i++){
        if(relations[i].at(0) == '2'){
            value += 1;
        }
        else if(relations[i].at(0) == '3'){
            value += 5;
        }
        else if(relations[i].at(0) == '4'){
            value += 7;
        }
    }
    value_str = to_string(value);
    relations[relations.size()-1] = value_str;
}

void check_adds_to_set(string& current_set, string card){
    // Current set in form:
    // el = n-slh or n-ns, eg 3-h3-5 or 2-5hc or 3-st-q
    int size;
    string new_size;
    // If(same suit)
    if(current_set.at(2) == card.back()){
        int min_val, max_val;
        string min_val_str, max_val_str;
        // Get min_value
        if(current_set.at(3) == 't'){
            min_val = 10;
        }
        else{
            min_val = eval_card(current_set.substr(3,1)+card.back(),false);
        }
        // Get max_value
        if(current_set.at(4) == 't'){
            max_val = 10;
        }
        else{
            max_val = eval_card(current_set.substr(5,1)+card.back(),true);
        }
        // Update the min_val
        if((min_val != 1)&&(min_val != 14)){
            // If(card_val == min_val - 1) and min_val > 1
            // Note if it is the minimum value aces must be low
            if(eval_card(card,false) == min_val-1){
                min_val -= 1;
            }
        }
        // Update the max_val
        if((max_val != 1)&&(max_val != 14)){
            // If(card_val == max_val + 1) and max_val < 14
            // Note if it is the maximum value aces must be low
            if(eval_card(card,true) == max_val+1){
                max_val += 1;
            }
        }
        // Convert them to a strings
        min_val_str = val_to_string(min_val);
        max_val_str = val_to_string(max_val);
        // Update the current_set string
        current_set = current_set.substr(0,3) 
                        + min_val_str + "-" + max_val_str;
        // Increment length by 1
        size = max_val - min_val + 1;
        new_size = to_string(size);
        current_set = new_size + current_set.substr(1);
    }
    // Else if(same type), eg 5h & 5s
    else if(((current_set.at(2) == 't')
            &&(all_but_last(card) == "10"))
            || (current_set.substr(2,1) == all_but_last(card))){
        // Add suit to end of current_set
        char suit = card.back();
        current_set = current_set.append(1, suit);
        // Increment length by 1
        size = stoi(current_set.substr(0,1)) + 1;
        new_size = to_string(size);
        current_set = new_size + current_set.substr(1);
    }
}

string val_to_string(int card_val){
    string card_str;
    if((card_val == 1)||(card_val == 14)){
        card_str = "a";
    }
    else if((card_val > 1)&&(card_val < 10)){
        card_str = to_string(card_val);
    }
    else if(card_val == 10){
        card_str = "t";
    }
    else if(card_val == 11){
        card_str = "j";
    }
    else if(card_val == 12){
        card_str = "q";
    }
    else if(card_val == 13){
        card_str = "k";
    }
    else{
        cout << "Error: val_to_string - not a valid input\
        int(" << card_val << "), must be >0 & <15" << endl;
    }
    return card_str;
}

int main(){
    // update_vector_value testing
    string card1, card2, result, again = "y";
    bool pair;
    while(again == "y"){
        cout << "Enter two cards:" << endl;
        cin >> card1 >> card2;
        result = check_pair(card1, card2);
        if(result != ""){
            cout << "These are a pair" << endl;
            cout << "result = " << result << endl;
        }
        else{
            cout << "These are not a pair" << endl;
        }
        cout << "Again? (y or n)" << endl;
        cin >> again;
    }

    // // Initialisations
    // int num_players, num_decks, num_put_down;
    // bool not_done = true;
    // string pile, put_down, discard_card;
    // vector <string> put_down_cards;
    // vector<vector<string>> scores;

    // // Initial user IO
    // cout << "Welcome to the rummy game" << endl;
    // cout << "How many people are playing?" << endl;
    // cin >> num_players;
    // cout << "How many decks are we playing with?" << endl;
    // cin >> num_decks;
    // cout << num_players << " people are playing and" << \
    // "we are playing with " << num_decks << " decks" \
    // << endl;

    // vector<player> vp; 
    // string name_tmp, out_tmp;
    // plist l = NULL;
    // cout << "Input player names (in order one at a time)" << endl;

    // // Get a data structure of people in game
    // for(int i = 0; i < num_players; i++){
    //     out_tmp = (i == 0) ? "dealer: " : "name: ";
    //     cout << out_tmp;
    //     cin >> name_tmp;
    //     plist tmp_p = new player;
    //     tmp_p->name = name_tmp;
    //     tmp_p->next = l;
    //     l = tmp_p;
    // }
    // cout << "The Players:\n";
    // plist rev_l = reverse_list(l);
    // plist looped_list = loop_list(rev_l);

    // // Initialise hands
    // for(int i = 0; i < num_players; i++){
    //     looped_list->initialise_hands_v();
    //     looped_list->view_hand_v();
    //     looped_list = looped_list->next;
    // }

    // // Initialise the decks
    // two_decks decks;
    // decks.initialise_decks_v(num_decks, num_players);
    // decks.view_decks_v();

    // // Start left of the dealer
    // looped_list = looped_list->next;
    // cout << "The first person is " << looped_list->name
    // << endl;
    // looped_list->view_hand_v();
    // while(not_done){
    //     if(looped_list->name != "cpu"){
    //         cout << looped_list->name << "'s go\n";
    //         cout << "Original Hand and Decks" << endl;
    //         looped_list->view_hand_v();
    //         decks.view_decks_v();
    //         // For debugging
    //         // looped_list->set_hand();
    //         // cout << "Post set_hand hand" << endl;
    //         // looped_list->view_hand_v();
    //         // Ask which pile they picked up from, card 
    //         // etc
    //         cout << "blind or discard? (b or d)\n";
    //         cin >> pile;
    //         // Update their hand and the deck
    //         looped_list->pick_up_v(decks, pile);
    //         // Check blind pile doesn't need to be flipped
    //         decks.check_flip_decks();
    //         // Ask if they put anything down on the table
    //         cout << "Did they put anything down (y or n)\n";
    //         cout << "(Only give the first set if multiple sets)\n";
    //         cin >> put_down;
    //         if(put_down == "y"){
    //             while(put_down == "y"){
    //                 cout << "How many cards did they put down?\n";
    //                 cin >> num_put_down;
    //                 cout << "Which cards did they put down?\n";
    //                 for(int i=0; i<num_put_down; i++){
    //                     cin >> put_down;
    //                     put_down_cards.push_back(put_down);
    //                 }
    //                 // Put down those cards
    //                 looped_list->put_down_v(put_down_cards);
    //                 put_down_cards.clear();
    //                 cout << "Did they put anything else down? (y or n)\n";
    //                 cin >> put_down;
    //             }
    //         }
    //         else if(put_down != "n"){
    //             cout << "Error: main - Invalid input, must be y or n";
    //         }
    //         //  Ask what they discarded, update hand and deck
    //         cout << "What card did they discard?\n";
    //         cin >> discard_card;
    //         looped_list->discard_v(decks, discard_card);
    //         cout << "Final Hand and Decks" << endl;
    //         looped_list->view_hand_v();
    //         decks.view_decks_v();
    //     }
    //     // else{ 
    //     //  check what the top card on discard pile is
    //     //  pick_blind = make_pick_up_decision(discard)
    //     //  if(pick_blind){
    //     //      update hand and blind_pile}
    //     //  else{
    //     //      update hand and discard_pile}
    //     //  decide what to put down and throw away
    //     //  update hand and discard_pile

    //     // if(len(current_player.hand) == 0){
    //     //  not_done = false}
    //     // current_player = current_player.next
    //     if(looped_list->cards_left == 0){
    //         not_done = false;
    //     }
    //     looped_list = looped_list->next;
    // }

    // // Find winner
    // get_scores(num_players, scores, looped_list);
    return 0;
}

plist loop_list(plist in_lst){
    plist first_node = in_lst;
    while(in_lst->next != NULL){
        in_lst = in_lst->next;
    }
    in_lst->next = first_node;
    return first_node;
}

plist reverse_list(plist in_lst){
    plist rev_lst = NULL; 
    while(in_lst != NULL){
        plist tmp_p = new player;
        tmp_p->name = in_lst->name;
        tmp_p->next = rev_lst;
        rev_lst = tmp_p;
        in_lst = in_lst->next;
    }
    return rev_lst;
}

void print_lst(plist in_lst){
    in_lst;
    while(in_lst != NULL){
        cout << in_lst->name << endl;
        in_lst = in_lst->next;
    }
}

string all_but_last(string str){
    return str.substr(0, str.size()-1);
}

bool are_aces_high(const vector <string>& put_down_cards){
    bool aces_high = true;
    for(int i=0; i<put_down_cards.size(); i++){
        if(all_but_last(put_down_cards[i]) == "2"){
            aces_high = false;
        }
    }
    return aces_high;
}

bool check_valid_set(vector <string>& put_down_cards){
    bool same_suit=true, same_num=true, valid=false;
    bool consecutive = true, aces_high = true;
    string tmp;
    vector <bool> visited(put_down_cards.size(), false);
    // Check they are all either the same number or have
    // the same suit
    for(int i=0; i<put_down_cards.size()-1; i++){
        if(put_down_cards[i].back() != put_down_cards[i+1].back()){
            same_suit = false;
        }
        if(all_but_last(put_down_cards[i]) 
            != all_but_last(put_down_cards[i+1])){
            same_num = false;
        }
        if((all_but_last(put_down_cards[i]) == "2")
            || (all_but_last(put_down_cards[i+1]) == "2")){
                aces_high = false;
        }
    }
    // If all the same number check the 3<=length<=4
    if(same_num 
        && (put_down_cards.size()>2) 
        && (put_down_cards.size()<5)){
        valid = true;
    }
    // If all the same suit check they are consecutive
    // (Don't need to check less than the size of the hand
    //  because I already checked all the cards were in 
    //  the player's hand)
    if(same_suit && (put_down_cards.size()>2)){
        int min = eval_card(put_down_cards[0], aces_high);
        int max = eval_card(put_down_cards[0], aces_high);
        // Get min and max
        for(int i=1;i<put_down_cards.size(); i++){
            if(eval_card(put_down_cards[i], aces_high)<min){
                min = eval_card(put_down_cards[i], aces_high);
            }
            else if(eval_card(put_down_cards[i], aces_high)>max){
                max = eval_card(put_down_cards[i], aces_high);
            }
        }
        // Check numbers numbers are consecutive
        if(max - min + 1 == put_down_cards.size()){
            for(int i=0; i<put_down_cards.size(); i++){
                if(!visited[eval_card(put_down_cards[i], aces_high)-min]){
                    visited[eval_card(put_down_cards[i], aces_high)-min] = true;
                }
                else{consecutive=false;}
            }
            valid = consecutive;
        }
        // Bubblesort run for niceness
        for(int i=0; i<put_down_cards.size(); i++){
            for(int j=0; j<put_down_cards.size()-1; j++){
                if(eval_card(put_down_cards[j+1], aces_high)
                    <eval_card(put_down_cards[j], aces_high)){
                    tmp = put_down_cards[j];
                    put_down_cards[j] = put_down_cards[j+1];
                    put_down_cards[j+1] = tmp;
                }
            }
        }
    }
    return valid;
}

int eval_card(const string& str, bool aces_high){
    string num_part = all_but_last(str);
    int evalled;
    if((num_part == "j")||(num_part == "J")){
        evalled = 11;
    }
    else if((num_part == "q")||(num_part == "Q")){
        evalled = 12;
    }
    else if((num_part == "k")||(num_part == "K")){
        evalled = 13;
    }
    else if((num_part == "a")||(num_part == "A")){
        if(aces_high){evalled = 14;}
        else{evalled = 1;}
    }
    else{
        evalled = stoi(num_part);
    }
    return evalled;
}

void get_scores(int num_players,
                vector<vector<string>>& scores,
                plist looped_list){
    vector<string> tmp_vec{"name","score"};
    // Go through each player
    for(int i=0; i<num_players; i++){
        scores = looped_list->get_score(scores);
        looped_list = looped_list->next;
    }
    // Order vector in order of score (bubblesort)
    for(int i=0; i<num_players; i++){
        for(int j=1; j<num_players; j++){
            if(stoi(scores[j][1]) > stoi(scores[j-1][1])){
                tmp_vec = scores[j];
                scores[j] = scores[j-1];
                scores[j-1] = tmp_vec;
            }
        }
    }
    // Print scores in order
    cout << "\nFinal Scores:\n";
    for(int i=0; i<num_players; i++){
        cout << scores[i][0] << ": " << scores[i][1] << endl;
    }
}



