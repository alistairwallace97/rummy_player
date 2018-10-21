// A program for playing the card game rummy. 
// Stores the players in a linked list of items of type
// player. In the main it will set up all the necessary
// variables, then iterate around a circular linked list
// until the exit condition is met. (One of the players 
// is out)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

// Define a class for the two piles, the discard and blind
// piles.
class two_decks {
        // string* blind_pile;
        // string* discard_pile;
        vector<string> blind_pile_v;
        vector<string> discard_pile_v;
    public:
        string discard_top;
        int total_cards;
        int total_cards_v;
        int current_num_blind;
        // void initialise_decks(int num_decks, 
        //                       int num_players);
        void initialise_decks_v(int num_decks, 
                              int num_players);
        // void view_decks();
        void view_decks_v();        
        // void reset_discard_top();
        // string remove_top_card(string pile);
        string remove_top_card_v(string pile);
        string add_to_discard_v(string card){
            discard_pile_v.push_back(card);
        }
};

// Define a class of type player
class player {
        string* hand;    // Max length 7
        int current_score; // Min -95, max +95
        vector<string> hand_v;
    public:
        string name;
        string* table_hand; // Max length 7
        vector<string> table_hand_v;
        int cards_left = 7; //Max 7, min 0
        // void initialise_hands();
        void initialise_hands_v();
        // void view_hand();
        void view_hand_v();
        // void pick_up(two_decks& decks, string pile);
        void pick_up_v(two_decks& decks, string pile);
        void put_down_v(vector <string> put_down_cards);
        bool check_in_hand(string card);
        void increment_score(int num) {
            current_score += num;
        }
        void discard_v(two_decks& decks, string card);
        vector<vector<string>> get_score(vector<vector<string>>& scores);
        player* next;
};

typedef player* plist;

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

// void two_decks::initialise_decks(int num_decks, 
//                                  int num_players){
//     total_cards = (52*num_decks) - (7*num_players);
//     current_num_blind = total_cards -1;
//     string* blind_tmp;
//     string* disc_pile_tmp;
//     blind_tmp = new string[current_num_blind];
//     disc_pile_tmp = new string[1];
//     for(int i=0; i<current_num_blind; i++){
//         blind_tmp[i] = "unk";
//     }
//     blind_pile = blind_tmp;
//     discard_pile = disc_pile_tmp;
//     cout << "What is the first card on the discard pile?\n";
//     cin >> discard_top;
//     discard_pile[0] = discard_top;
// }

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

// void two_decks::view_decks(){
//     cout << "entered view_decks" << endl;
//     cout << "current_num_blind = " << current_num_blind << endl;
//     cout << "\nThe current decks\nblind:" << endl;
//     for(int i=0; i<current_num_blind; i++){
//         cout << blind_pile[i] << ", ";
//     }
//     cout << endl << "\ndiscard:" << endl;
//     cout << "(total_cards - current_num_blind) = " << 
//         (total_cards - current_num_blind) << endl;
//     cout << "discard_pile[0] = " << discard_pile[0] << endl;
//     for(int i=0; i<(total_cards - current_num_blind); i++){
//         cout << discard_pile[i] << ", ";
//     }
//     cout << "finished discard_pile" << endl;

// }

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

// void two_decks::reset_discard_top(){
//     int discard_size = total_cards - current_num_blind;
//     discard_top = discard_pile[discard_size-1];
// }

// string two_decks::remove_top_card(string pile){
//     string top_card;
//     if(pile == "b"){
//         // Remove the first element[0] of the blind pile
//         top_card = blind_pile[0];
//         string* new_blind_pile;
//         new_blind_pile = new string[current_num_blind-1];
//         for(int i=0; i<current_num_blind-1; i++){
//             new_blind_pile[i] = blind_pile[i+1];
//         }
//         cout << "printing old blind_pile:" << endl;
//         for(int i=0; i<current_num_blind; i++){
//             cout << blind_pile[i] << ", ";
//         } 
//         cout << endl << "new_blind_pile:" << endl;
//         for(int i=0; i<current_num_blind-1; i++){
//             cout << new_blind_pile[i] << ", ";
//         } 

//         // string* tmp = blind_pile;
//         blind_pile = new_blind_pile;
//         current_num_blind--;
//         cout << endl << "next blind_pile:" << endl;
//         for(int i=0; i<current_num_blind; i++){
//             cout << blind_pile[i] << ", ";
//         } 
//         cout << endl;

//         // delete[] tmp;
//     }
//     else if(pile == "d"){
//         // Remove last element [-1] of the discard pile
//         int discard_size = total_cards - current_num_blind;
//         top_card = discard_pile[discard_size-1];
//         string* new_discard_pile;
//         new_discard_pile = new string[discard_size-1];
//         for(int i=0; i<discard_size-1; i++){
//             new_discard_pile[i] = discard_pile[i+1];
//         }
//         delete[] discard_pile;
//         discard_pile = new_discard_pile;
//     }
//     else{
//         cout << "Error: two_decks::remove_top_card - pile \
//         input (" << pile << ") was not in the right \
//         input.\nShould be either 'b' or 'd'.";
//         top_card = "Error";
//     }
//     return top_card;
// }

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

// void player::initialise_hands(){
//     if(name == "cpu"){
//         cout << "\nnot working for cpu yet" << endl;
//     }
//     // Doesn't seperately deal with the case of name not
//     // being initialised.
//     else{
//         string* hand_tmp;
//         string* table_hand_tmp;
//         int max_size = 7;
//         // Needs a max_size of 7+1 because during a turn
//         // a player will have 8 cards before they throw 
//         // away.
//         hand_tmp = new string[max_size+1];
//         table_hand_tmp = new string[max_size];
//         for(int i=0; i<max_size; i++){
//             hand_tmp[i] = "unk";
//             table_hand_tmp[i] = "n/a";
//         }
//         hand = hand_tmp;
//         cards_left = max_size;
//         table_hand = table_hand_tmp;
//     }
// }

void player::initialise_hands_v(){
    for(int i=0; i<7; i++){
        hand_v.push_back("unk");
    }
}

// void player::view_hand(){
//     cout << "\nname: " << name;
//     cout << "\nhand: ";
//     for(int i=0; i<cards_left; i++){
//         cout << hand[i] << ", ";
//     }
//     cout << "\ntable_hand: ";
//     for(int i=0; i<cards_left; i++){
//         cout << table_hand[i] << ", ";
//     }
//     cout << endl;
// }

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

// void player::pick_up(two_decks& decks, string pile){
//     cout << "entered pick_up" << endl;
//     if(pile == "b"){
//         cout << "if(pile == 'b')" << endl;
//         // Delete the first element of the blind_pile
//         //  - Set a new pointer to point to the second el
//         //  - Delete pointer to the first element
//         //  - Set decks.blind_pile to the new pointer.
//         string top_card;
//         cout << "decks->current_num_blind = " << 
//             decks.current_num_blind << endl;
//         top_card = decks.remove_top_card(pile);
//         cout << "decks->current_num_blind = " << 
//             decks.current_num_blind << endl;
//         cout << "top_card = " << top_card << endl;
//         // Add unknown card to players hand.
//         // string* tmp_p = decks.;
//         hand[cards_left] = top_card;
//         cout << "hand[cards_left] = top_card;" << endl;
//     }
//     else if(pile == "d"){
//         // Add known card to players hand
//         // hand[cards_left] = decks.discard_top;
//         // Delete the last element of the discard pile
//         hand[cards_left] = decks.remove_top_card(pile);
//         // Set discard_top to be the new last element.
//         decks.reset_discard_top();
//     }
//     else{
//         cout << "Error: player::pick_up - pile input (" <<
//         pile << ") was not in the right input.\nShould be \
//         either 'b' or 'd'." << endl;
//     }
// }

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
        // cout << "i2 = " << i << endl;
        // cout << "card = " << card << endl;
        // cout << "hand_v[i] = " << hand_v[i] << endl;
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
        cout << "\nhand_v[0] =\n" << endl;
        for(int i=0; i<cards_left; i++){
            cout << hand_v[i] <<", ";
        }
        cout << endl;
        // Subtract the value of the card from current_score 
        current_score -= eval_card(hand_v[0], true);
        cout << "current_score = " << current_score << endl;
        // Remove that card from the hand
        hand_v.erase(remove(hand_v.begin(), hand_v.end(), hand_v[0]), hand_v.end());
        cout << "\nhand_v[0] =\n" << endl;
        for(int i=0; i<cards_left; i++){
            cout << hand_v[i] <<", ";
        }
        cout << endl;
    }
    // Add [name, current_score] to scores
    vector<string> name_and_score;
    name_and_score.push_back(name);
    name_and_score.push_back(to_string(current_score));
    scores.push_back(name_and_score);
    return scores;
}


int main(){
    // Initialisations
    int num_players, num_decks, num_put_down;
    bool not_done = true;
    string pile, put_down, discard_card;
    vector <string> put_down_cards;
    vector<vector<string>> scores;

    // Initial user IO
    cout << "Welcome to the rummy game" << endl;
    cout << "How many people are playing?" << endl;
    cin >> num_players;
    cout << "How many decks are we playing with?" << endl;
    cin >> num_decks;
    cout << num_players << " people are playing and" << \
    "we are playing with " << num_decks << " decks" \
    << endl;

    vector<player> vp; 
    string name_tmp, out_tmp;
    plist l = NULL;
    cout << "Input player names (in order one at a time)" << endl;

    // Get a data structure of people in game
    for(int i = 0; i < num_players; i++){
        out_tmp = (i == 0) ? "dealer: " : "name: ";
        cout << out_tmp;
        cin >> name_tmp;
        plist tmp_p = new player;
        tmp_p->name = name_tmp;
        tmp_p->next = l;
        l = tmp_p;
    }
    cout << "The Players:\n";
    plist rev_l = reverse_list(l);
    plist looped_list = loop_list(rev_l);

    // Initialise hands
    for(int i = 0; i < num_players; i++){
        // looped_list->initialise_hands();
        looped_list->initialise_hands_v();
        // looped_list->view_hand();
        looped_list->view_hand_v();
        looped_list = looped_list->next;
    }

    // Initialise the decks
    two_decks decks;
    // cout << "initialise_decks" << endl;
    // decks.initialise_decks(num_decks, num_players);
    // cout << "initialise_decks_v" << endl;
    decks.initialise_decks_v(num_decks, num_players);
    // cout << "view_decks" << endl;
    // decks.view_decks();
    // cout << "view_decks_v" << endl;
    decks.view_decks_v();

    // Start left of the dealer
    looped_list = looped_list->next;
    cout << "The first person is " << looped_list->name
    << endl;
    looped_list->view_hand_v();
    while(not_done){
        if(looped_list->name != "cpu"){
            cout << looped_list->name << "'s go\n";
            // Ask which pile they picked up from, card 
            // etc
            cout << "blind or discard? (b or d)\n";
            cin >> pile;
            // Update their hand and the deck
            // looped_list->pick_up(decks, pile);
            looped_list->pick_up_v(decks, pile);
            // View pick up changes 
            cout << "Original Hand and Decks" << endl;
            looped_list->view_hand_v();
            decks.view_decks_v();
            // Ask if they put anything down on the table
            cout << "Did they put anything down (y or n)\n";
            cin >> put_down;
            if(put_down == "y"){
                cout << "How many cards did they put down?\n";
                cin >> num_put_down;
                cout << "Which cards did they put down?\n";
                for(int i=0; i<num_put_down; i++){
                    cin >> put_down;
                    put_down_cards.push_back(put_down);
                }
                // Put down those cards
                looped_list->put_down_v(put_down_cards);
            }
            else if(put_down != "n"){
                cout << "Error: main - Invalid input, must be y or n";
            }
            //  Ask what they discarded, update hand and deck
            cout << "What card did they discard?\n";
            cin >> discard_card;
            looped_list->discard_v(decks, discard_card);
            cout << "Final Hand and Decks" << endl;
            looped_list->view_hand_v();
            decks.view_decks_v();
        }
        // else{ 
        //  check what the top card on discard pile is
        //  pick_blind = make_pick_up_decision(discard)
        //  if(pick_blind){
        //      update hand and blind_pile}
        //  else{
        //      update hand and discard_pile}
        //  decide what to put down and throw away
        //  update hand and discard_pile

        // if(len(current_player.hand) == 0){
        //  not_done = false}
        // current_player = current_player.next
        if(looped_list->cards_left == 0){
            not_done = false;
        }
    }

    // Find winner
    get_scores(num_players, scores, looped_list);
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
        cout << "min = " << min << ", max = " << max << endl;
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
            for(int j=0; j<put_down_cards.size()-1; i++){
                if(eval_card(put_down_cards[j+1], aces_high)
                    <eval_card(put_down_cards[j], aces_high)){
                    tmp = put_down_cards[j];
                    put_down_cards[j] = put_down_cards[j+1];
                    put_down_cards[j+1] = tmp;
                }
            }
        }
    }
    cout << "returns valid = " << valid << endl;
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
        cout << scores[i][0] << ": " << scores[i][1];
    }
}



