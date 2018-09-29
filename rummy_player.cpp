// A program for playing the card game rummy. 
// Stores the players in a linked list of items of type
// player. In the main it will set up all the necessary
// variables, then iterate around a circular linked list
// until the exit condition is met. (One of the players 
// is out)

#include <iostream>
#include <string>
#include <vector>
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
};

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
        // Debug Printing
        // cout << "b - top_card = " << top_card << endl;
    }
    else if(pile == "d"){
        // Debug Printing
        // cout << "size_0 = " << discard_pile_v.size() << endl;
        // cout << "discard_pile_v0:\n";
        // for(int i=0; i<discard_pile_v.size(); i++){
        //     cout << discard_pile_v[i] << ", ";
        // }
        // cout << endl;
        top_card = discard_pile_v.back();
        discard_pile_v.pop_back();
        // More Debug Printing
        // cout << "size_1 = " << discard_pile_v.size() << endl;
        // cout << "discard_pile_v1:\n";
        // for(int i=0; i<discard_pile_v.size(); i++){
        //     cout << discard_pile_v[i] << ", ";
        // }
        // cout << "d - top_card = " << top_card << endl;

        // discard_pile_v.erase(discard_pile_v.end());
    }
    else{
        cout << "Error: two_decks::remove_top_card_v - pile \
        input (" << pile << ") was not in the right \
        input.\nShould be either 'b' or 'd'.";
        top_card = "Error";
    }
    return top_card;
}


// Define a class of type player
class player {
        string* hand;    // Max length 7
        int current_score; // Min -95, max +95
        vector<string> hand_v;
    public:
        string name;
        string* table_hand; // Max length 7
        vector<string> table_hand_v;
        // void initialise_hands();
        void initialise_hands_v();
        // void view_hand();
        void view_hand_v();
        // void pick_up(two_decks& decks, string pile);
        void pick_up_v(two_decks& decks, string pile);
        // put_down(self)
        // throw_away(delf, deck)
        int cards_left; // Max 7, min 0
        player* next;
};

typedef player* plist;

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
        cards_left = 7;
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

plist reverse_list(plist in_lst);
void print_lst(plist in_lst);
plist loop_list(plist in_lst);

int main(){
    // Initialisations
    int num_players, num_decks;
    bool not_done = true;
    string pile;

    // // Initial user IO
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
            // looped_list->pick_up(decks, pile);
            looped_list->pick_up_v(decks, pile);
            decks.view_decks_v();
            looped_list->view_hand_v();
        //  Update their hand and the deck
        //  Ask if they put anything down on the table
        //  Update their table_hand
        //  Ask what they discarded, update hand and deck
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
        not_done = false;
    }

    // Find winner

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