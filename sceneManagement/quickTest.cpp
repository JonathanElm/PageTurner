#include "../menu/playMenu.hpp"
#include "quickTest.hpp"
#include <iostream>

quickTest::quickTest(storyMenu * stry, scene * active){
    story = stry;
    activeScene = active;
}

void quickTest::run(){
        bool userWantsToQuit = false;
        while(!userWantsToQuit){
        int userAction = 0;
        //Prints title.
        std::cout << "========================================================" << std::endl;
        std::cout << activeScene.getTitle() << std::endl;
        std::cout << "========================================================" << std::endl;
        //Prints text.
        activeScene.printText();
        //Prints choices.
        for(int c = 0; c < activeScene.choices.size(); c++){
            for(int r = 0; r < ownedTags->size(); r++){
                for(int x = 0; x < activeScene.choices[c]->required.size(); x++){
                    if(ownedTags->operator[](r).name == activeScene.choices[c]->required[x].name){
                        if(ownedTags->operator[](r).amount >= activeScene.choices[c]->required[x].amount){
                            std::cout << c+1 << ") " << activeScene.choices[c]->text << std::endl;
                        }
                    }
                }
            }
        }
        std::cout << "Type -1 to end this program." << std::endl;
        std::cout << "Type -2 to go back to the main menu." << std::endl;
        std::cin >> userAction;
        //Handles a line selection.
        if(!std::cin.fail() && userAction > 0 && userAction <= activeScene.choices.size()){
            activeScene = activeScene.choices[userAction-1]->scene;
            for(int c = 0; c < activeScene.choices[userAction-1]->gives.size(); c++){
                bool foundSlot = false;
                for(int r = 0; r < ownedTags->size(); r++){
                    if(ownedTags->operator[](r).name == activeScene.choices[userAction-1]->gives[c].name){
                        ownedTags->operator[](r).amount += activeScene.choices[userAction-1]->gives[c].amount;
                        foundSlot = true;
                    }
                }
                if(!foundSlot){
                    tag bip;
                    bip.amount = activeScene.choices[userAction-1]->gives[c].amount;
                    bip.name = activeScene.choices[userAction-1]->gives[c].name;
                    ownedTags->push_back(bip);
                }
            }
        }
        //Handles any and all user actions that are for quit or leaving this scene.
        switch(userAction){
            case -2:{
                userWantsToQuit = true;
                backPedal();
                break;
            }
            case -1:{
                userWantsToQuit = true;
                quit();
                break;
            }
        };
    }

    void quickTest::quit(){
        storyMenu->setActive = false;
        return;
    }
}
