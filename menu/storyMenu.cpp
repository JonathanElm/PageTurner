#include <iostream>
#include <algorithm>
#include "../sceneManagement/quickTest.hpp"
#include "../sceneManagement/sceneManager.hpp"
#include "storyMenu.hpp"

//5/20/20
storyMenu::storyMenu(){
    //Default constructor for the class.
    return;
}

void storyMenu::setParent(titleMenu* mm){
    //Sets the parent of the menu.
    title = mm;
    return;
}

void storyMenu::setScene(scene * entry){
    //Sets the active scene.
    activeScene = entry;
    return;
}

void storyMenu::setQT(quickTest * qt){
    //Establishes the qT.
    qT = qt;
    return;
}

void storyMenu::backPedal(){
    //Takes the story back to the makeMenu.
    setActive = false;
    title->setActive = true;
    return;
}

void appendScenes(std::vector<scene>& listOfScenes, scene* entry){
    //error is here!
    bool found = false;
    for(int c = 0; c < listOfScenes.size(); c++){
        if(entry->getTitle() == listOfScenes[c].getTitle()){
            found = true;
        }
    }
    if(!found){
        listOfScenes.push_back(*entry);
    }
    for(int c = 0; c < entry->choices.size(); c++){
        appendScenes(listOfScenes,entry->choices[c]->linkScene);
    }
    return;
}

std::vector<scene *> storyMenu::printMenu(){
    //Displays the menu;
    int userInput = 0;
    std::cout << "========================================================" << std::endl;
    std::cout << "|                      Edit a Story                    |" << std::endl;
    std::cout << "========================================================" << std::endl;
    std::cout << "| 1) Read Story                                        |" << std::endl;
    std::cout << "| 2) Select Story                                      |" << std::endl;
    std::cout << "| 3) Make a New Story                                  |" << std::endl;
    std::cout << "| 4) Return to Main Menu                               |" << std::endl;
    std::cout << "| 5) Quit                                              |" << std::endl;
    std::cout << "========================================================" << std::endl;
    std::cin >> userInput;
        //Accessess and processes user input.
        switch(userInput){
        case 1:{
            if(!activeScene){
                std::cout << "No Story Selected. Please select a story first." << std::endl;
            }
            else{
                qT->run(activeScene);
            }
            break;
        }
        case 2:{
            //Need to do some mass story selection drop down for the user. starting and recieving from main. So retrieval has to be done by main.
            if(titleScenes.size() > 0){
                bool quit = false;
                while(!quit){
                    int input = 0;
                    std::cout << "========================================================" << std::endl;
                    std::cout << "|               Please Select a Scene                  |" << std::endl;
                    std::cout << "========================================================" << std::endl;
                    for(int c = 0; c < titleScenes.size(); c++){
                        std::cout << c+1 << ") " << titleScenes[c]->getTitle() << "." << std::endl;
                    }
                    std::cout << titleScenes.size()+1 << ") Edit Selected Scene." << std::endl;
                    std::cout << titleScenes.size()+2 << ") Quit." << std::endl;
                    std::cin >> input;
                    std::cin.clear();
                    std::cin.ignore();
                    if(input > 0 && input <= titleScenes.size()){
                        activeScene = titleScenes[input-1];
                        std::cout << "Active scene set to " << titleScenes[input-1]->getTitle() << " ." << std::endl;
                    }
                    else if(input == titleScenes.size()+1){
                        if(!activeScene){
                            std::cout << "No scene selected, please choose a scene before editing." << std::endl;
                        }
                        else{
                            std::vector<scene> sceneForBook;
                            sceneManager * sceneController = new sceneManager();
                            appendScenes(sceneForBook,activeScene);
                            sceneController->setScenes(sceneForBook);
                            sceneController->sceneSelection();
                            quit =  true;
                        }
                    }
                    else if(input == titleScenes.size()+2){
                        std::cout << "Returning to Edit Story Menu." << std::endl;
                        quit =  true;                        
                    }
                    else{
                        std::cout << "Invalid input." << std::endl;
                    }
                }
                
            }
            else{
                //Handles scene return.
                std::cout << "No Scenes Found. Making New Scene." << std::endl;
                scene * newScene = new scene();
                std::cin.clear();
                newScene->editScene();
                titleScenes.push_back(newScene);
            }
            break;
        }
        case 3:{
            std::cout << "Making New Scene." << std::endl;
            scene * newScene = new scene();
            std::cin.clear();
            newScene->editScene();
            titleScenes.push_back(newScene);
        }
        case 4:{
            backPedal();
            break;
        }
        case 5:{
            quit();
            break;
        }
        default:{
            std::cin.ignore();
            std::cin.clear();
        }
    };
    return titleScenes;
}

void storyMenu::setScenes(std::vector<scene *> scenes){
    titleScenes = scenes;
    return;
}

void storyMenu::quit(){
    bool notDone = true;
    while(notDone){
        std::cout << "Are you sure you want to close this whole program? (y/n)" << std::endl;
        char input;
        std::cin >> input;
        switch(input){
            case 'y':{
                notDone = false;
                setActive = false;
                break;
            }
            case 'n':{
                notDone = false;
                break;
            }
            default:{
                std::cin.clear();
                std::cin.ignore();
                break;
            }
        };
    }
    return;
}
