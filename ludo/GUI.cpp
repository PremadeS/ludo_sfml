#include"GUI.h"
bool GUI::sleeper(int n)
{
    for (int i = 0; i < 1000 * n; ++i)
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
         if (event.type == sf::Event::MouseButtonPressed)
             if (event.mouseButton.button == sf::Mouse::Left)
                   return true;
        
    }
    return false;
}
GUI::GUI(sf::RenderWindow& _window) :window{ _window }, Ludo{ _window }, players{ nullptr } {}
int GUI::rollDice(sf::Sprite& sBoard, sf::CircleShape**& pieceShape, const int playerCount, const int pieceCount, sf::Sprite**& _characters, int turn)
{
    window.clear();
    window.draw(sBoard);
    drawPieces(pieceShape, playerCount, pieceCount, _characters, turn);
    window.display();


    sf::Texture shadow;
    shadow.loadFromFile("shadow.png");
    sf::Sprite shadowShape(shadow);
    shadowShape.setPosition(900 + 10, 280+ 10);            //Shadow for Dice
    shadowShape.setScale(0.4, 0.4);
    

    sf::Texture faces[6];
    sf::Sprite faceShapes[6];
    for (int i = 0; i < 6; ++i) {
        faces[i].loadFromFile(to_string(i + 1) + ".png");
    }
    for (int i = 0; i < 6; ++i)
    {
        faceShapes[i].setTexture(faces[i]);
        faceShapes[i].setScale(0.4, 0.4);
        faceShapes[i].setPosition(900, 280);

    }

    sf::Sprite extraSix(faces[5]);          //For small six :)

    int checkSix = 0;
    int steps = 0;
    bool val = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (!(mousePos.x >= 1007 && mousePos.x <= 1254 && mousePos.y >= 582 && mousePos.y <= 691)) {
                    Dice d;
                    steps += d.roll();
                    cout << steps << endl;
                    window.clear();
                    window.draw(sBoard);

                    drawPieces(pieceShape, playerCount, pieceCount, _characters, turn);

                    if (steps >= 1 && steps <= 6)
                    {
                        window.draw(shadowShape);
                        window.draw(faceShapes[steps - 1]);
                    }
                    else if (steps > 0)
                    {
                        
                        window.draw(shadowShape);

                        window.draw(faceShapes[steps - (checkSix * 6) - 1]);
                        for (int i = 0; i < checkSix; ++i)
                        {
                            if(i==0)
                            extraSix.setPosition(730, 600);
                            else
                                extraSix.setPosition(850, 600);

                            extraSix.setScale(0.2, 0.2);
                            window.draw(extraSix);

                        }
                    }
                    window.display();
                }
                else
                    return -1;      // End Turn called :D
                if (steps % 6 == 0) {
                    ++checkSix;
                    if (checkSix == 3) 
                    {
                        sf::sleep(sf::seconds(1));
                        return 0;
                    }
                }
                else {
                    return steps;
                    break;
                }
            }
        }
    }

    return steps;

}
void GUI::makeShapes(sf::CircleShape**& pieceShape,const int playerCount,const int pieceCount)
{
    
    pieceShape = new sf::CircleShape * [playerCount];
    for (int i = 0; i < playerCount; ++i) {
        pieceShape[i] = new sf::CircleShape[pieceCount];
        for (int j = 0; j < pieceCount; ++j)
        {
            pieceShape[i][j].setRadius(10);
            pieceShape[i][j].setOutlineThickness(3);
            if (i == 0) {
                pieceShape[i][j].setFillColor(sf::Color::Red);
                pieceShape[i][j].setPosition(286 + (j * 41.5), 654);
            }
            else if (i == 1)
            {
                pieceShape[i][j].setFillColor(sf::Color(255,215,0));
                pieceShape[i][j].setPosition(97 + (j * 41.5), 477);
            }
            else if (i == 2)
            {
                pieceShape[i][j].setFillColor(sf::Color::Green);
                pieceShape[i][j].setPosition(98 + (j * 41.5), 215);
            }
            else if (i == 3)
            {
                pieceShape[i][j].setFillColor(sf::Color(255, 165, 0));
                pieceShape[i][j].setPosition(286 + (j * 41.5), 41);
            }
            else if (i == 4)
            {
                pieceShape[i][j].setFillColor(sf::Color::Magenta);
                pieceShape[i][j].setPosition(477 + (j * 41.5), 215);
            }
            else
            {
                pieceShape[i][j].setFillColor(sf::Color::Blue);
                pieceShape[i][j].setPosition(477 + (j * 41.5), 477);
            }
        }
    }

}
void GUI::drawPieces(sf::CircleShape**& pieceShape, const int playerCount, const int pieceCount,sf::Sprite**& _characters,int turn)
{
    for (int i = 0; i < playerCount; ++i)
    {
        for (int j = 0; j < pieceCount; ++j)
            window.draw(pieceShape[i][j]);
    }
    drawCharacters(_characters, playerCount,turn);
    drawTurns(turn);
}
bool GUI::pugGaiGoti(Game &Ludo,Piece * _piece,sf::CircleShape **&pieceShape)   
{
    Player* currPlayer = _piece->getPlayer();
    if (Ludo.pugGai(_piece))
    {
        cout << "HAHA";
        return true;
    }
        pieceShape[stoi(currPlayer->getPlayerID())][stoi(_piece->getPieceID())].setPosition(352, 400);
        return false;
}
void GUI::drawTurns(int turn)
{
    if (turn != -1)
    {
        sf::Texture currTurn;
        currTurn.loadFromFile(to_string(turn + 1) + "turn.png");
        sf::Sprite currTurnShape(currTurn);
        currTurnShape.setPosition(750, 80);
        //currTurnShape.setScale(0.4, 0.4);
        window.draw(currTurnShape);
    }
}
void GUI::drawCharacters(sf::Sprite**& _characters, int count, int turn)
{
    
    sf::Texture* texturesChar = new sf::Texture[count];
    _characters = new sf::Sprite * [count];
    for (int i = 0; i < count; ++i)
    {
        if (i == 0)
            texturesChar[i].loadFromFile("one.png");
        else if (i == 1)
            texturesChar[i].loadFromFile("two.png");
        else if (i == 2)
            texturesChar[i].loadFromFile("three.png");
        else if (i == 3)
            texturesChar[i].loadFromFile("four.png");
        else if (i == 4)
            texturesChar[i].loadFromFile("five.png");
        else
            texturesChar[i].loadFromFile("six.png");
    }
    sf::Color greyed(64, 64, 64);
    for (int i = 0; i < count; ++i)
    {
        _characters[i] = new sf::Sprite(texturesChar[i]);
        if (i == 0)
        {
            _characters[i]->setPosition(85, 630);
            if (turn == 0)
                _characters[i]->setScale(0.5, 0.5);
            else
            {
                _characters[i]->setScale(0.3, 0.3);
                _characters[i]->setColor(greyed);

            }
        }
        else if (i == 1)
        {
            _characters[i]->setPosition(180, 630);
            if (turn == 1)
                _characters[i]->setScale(0.22, 0.22);
            else
            {       _characters[i]->setScale(0.16, 0.16);
                    _characters[i]->setColor(greyed);
                    _characters[i]->setPosition(180, 600);

            }
            _characters[i]->setRotation(180);
        }
        else if (i == 2)
        {
            _characters[i]->setPosition(100, 65);
            if (turn == 2)
                _characters[i]->setScale(0.25, 0.25);
            else
            {
                _characters[i]->setScale(0.19, 0.19);
                _characters[i]->setColor(greyed);
                _characters[i]->setPosition(100, 100);

            }

        }
        else if (i == 3)
        {
            _characters[i]->setPosition(560, 105);
            if (turn == 3)
                _characters[i]->setScale(0.25, 0.25);
            else
            {
                _characters[i]->setScale(0.16, 0.16);
                _characters[i]->setColor(greyed);
                _characters[i]->setPosition(560, 75);

            }
            _characters[i]->setRotation(180);


        }
        else if (i == 4)
        {
            _characters[i]->setPosition(540, 90);
            if (turn == 4)
                _characters[i]->setScale(0.22, 0.22);
            else
            {
                _characters[i]->setScale(0.16, 0.16);
                _characters[i]->setColor(greyed);
                _characters[i]->setPosition(540, 115);

            }
            _characters[i]->setTextureRect(sf::IntRect(500, 0, -500, 500));

        }
        else
        {
            _characters[i]->setPosition(500, 565);
            if (turn == 5)
                _characters[i]->setScale(0.3, 0.3);
            else
            {
                _characters[i]->setScale(0.16, 0.16);
                _characters[i]->setColor(greyed);

            }

        }
        window.draw(*(_characters[i]));
    }
    
}
void GUI::welcome()
{
    sf::Texture texts[6];
    sf::Sprite sprites[6];

    for (int i = 0; i < 6; ++i)
    {
        texts[i].loadFromFile(to_string(i) + "initial.png");
        sprites[i].setTexture(texts[i]);
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        for (int i = 0; i < 6; ++i)
        {
            window.clear();
            window.draw(sprites[i]);
            window.display();
            sf::sleep(sf::seconds(0.03));
        }
       
        if (sleeper(100))
            break;
        
        for (int i = 5; i >= 0;--i)
        {

            window.clear();
            window.draw(sprites[i]);
            window.display();
            sf::sleep(sf::seconds(0.03));
        }
        if (sleeper(100))
            break;
    }
}
void GUI::teamCountSelect(int& teamCount)
{
    sf::Texture text;
    text.loadFromFile("teamsselect.png");
    sf::Sprite sprite(text);
    window.clear();
    window.draw(sprite);
    window.display();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                cout << mousePos.x << " " << mousePos.y << endl;
                if (mousePos.x >= 300 && mousePos.x <= 508 && mousePos.y >= 213 && mousePos.y <= 307)
                {
                    teamCount = 2;
                    break;
                }
                else if (mousePos.x >= 541 && mousePos.x <= 755 && mousePos.y >= 213 && mousePos.y <= 307)
                {
                    teamCount = 3;
                    break;
                }
            }
        }
        //window.display();

    }
}
void GUI::teamSelect(int& teamCount)
{
    sf::Texture text;
    text.loadFromFile("teamselect.png");
    sf::Sprite sprite(text);
    window.clear();
    window.draw(sprite);
    window.display();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                cout << mousePos.x << " " << mousePos.y << endl;
                if (mousePos.x >= 195 && mousePos.x <= 572 && mousePos.y >= 169 && mousePos.y <= 334)
                {
                    teamCount = 0;
                    break;
                }
                else if (mousePos.x >= 710 && mousePos.x <= 1088 && mousePos.y >= 165 && mousePos.y <= 339)
                {
                    teamCountSelect(teamCount);
                    break;
                }
            }
        }
        //window.display();

    }
}
void GUI::playerSelect(int& playerCount)
{
    sf::Texture text;
    text.loadFromFile("playerselect.png");
    sf::Sprite sprite(text);
    window.clear();
    window.draw(sprite);
    window.display();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                cout << mousePos.x << " " << mousePos.y << endl;
                if (mousePos.x >= 50 && mousePos.x <= 264 && mousePos.y >= 212 && mousePos.y <= 308)
                {
                    playerCount = 2;
                    break;
                    
                }
                else  if (mousePos.x >= 300 && mousePos.x <= 508 && mousePos.y >= 213 && mousePos.y <= 307)
                {
                    playerCount = 3;
                    break;
                }
                else if (mousePos.x >= 541 && mousePos.x <= 755 && mousePos.y >= 213 && mousePos.y <= 307)
                {
                    playerCount = 4;
                    break;
                }
                else if (mousePos.x >= 788 && mousePos.x <= 1006 && mousePos.y >= 213 && mousePos.y <= 307)
                {
                    playerCount = 5;
                    break;
                }
                else if (mousePos.x >= 1027 && mousePos.x <= 1244 && mousePos.y >= 213 && mousePos.y <= 307)
                {
                    playerCount = 6;
                    break;
                }
               
            }
        }
        //window.display();

    }
}
void GUI::pieceSelect(int& pieceCount)
{
    sf::Texture text;
    text.loadFromFile("pieceselect.png");
    sf::Sprite sprite(text);
    window.clear();
    window.draw(sprite);
    window.display();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                cout << mousePos.x << " " << mousePos.y << endl;
                if (mousePos.x >= 50 && mousePos.x <= 264 && mousePos.y >= 212 && mousePos.y <= 308)
                {
                    pieceCount = 1;
                    break;

                }
                else  if (mousePos.x >= 300 && mousePos.x <= 508 && mousePos.y >= 213 && mousePos.y <= 307)
                {
                    pieceCount = 2;
                    break;
                }
                else if (mousePos.x >= 541 && mousePos.x <= 755 && mousePos.y >= 213 && mousePos.y <= 307)
                {
                    pieceCount = 3;
                    break;
                }
                else if (mousePos.x >= 788 && mousePos.x <= 1006 && mousePos.y >= 213 && mousePos.y <= 307)
                {
                    pieceCount = 4;
                    break;
                }
               
            }
        }
        //window.display();

    }
}
void GUI::start(int teamCount,int playerCount,int pieceCount)
{
    int turn = 0, roll = 1;

    //ifstream rdr("data.txt");
    //Ludo.loadGame(rdr,teamCount, playerCount, pieceCount, turn);      //FOR LOADING FROM FILE :)  

    sf::Texture boardTexture;
    boardTexture.loadFromFile("board.png");

    sf::Sprite** characters{};
    sf::Sprite sBoard(boardTexture);
    sf::CircleShape** pieceShape{};

    sBoard.setPosition(0, 0);
    window.draw(sBoard);
    makeShapes(pieceShape, playerCount, pieceCount);    //Making and Drawing pieces
    drawPieces(pieceShape, playerCount, pieceCount, characters, -1);


    board = Ludo.startGame(playerCount, pieceCount, teamCount, players);
    
    
    //Ludo.loadPieceValues(rdr, teamCount, playerCount, pieceCount, turn, players);             // FOR LOADING FROM FILE :)
    //Ludo.setPosAfterLoad(teamCount, playerCount, pieceCount, turn, players, pieceShape);


    int r, c, x, y;

   

    drawPieces(pieceShape, playerCount, pieceCount, characters, turn);
    bool newTurn = true;
    
    while (window.isOpen())
    {

        if (newTurn)
            roll = rollDice(sBoard, pieceShape, playerCount, pieceCount,characters,turn);
        
        if (roll == 0)
        {
            ++turn;
            if (turn >= playerCount)
                turn = 0;
            continue;
        }
        bool unlock = false, notMoved = false;
        Piece* movedPiece{};
        string pieceID = "";
        int validator = Ludo.checkMove(x, y, r, c, board, players[turn], movedPiece, pieceID, unlock, roll);
        window.clear();
        window.draw(sBoard);
        //Ludo.saveGame(teamCount,playerCount,pieceCount,turn,players);
        if (validator == 1)
        {

            if (!unlock)
            {
                bool rolled = false;
                if (roll > 6)
                {
                    if (Ludo.movePiece(6, movedPiece->getPlayer(), pieceID, board, x, y))
                    {
                        roll -= 6;
                        rolled = true;
                    }
                    else
                    {
                        newTurn = false;
                        continue;
                    }
                }
                else
                {
                    if (!Ludo.movePiece(roll, movedPiece->getPlayer(), pieceID, board, x, y))
                    {
                        newTurn = false;
                        continue;
                    }
                }
                if (rolled)
                    newTurn = false;
                else if (roll <= 6&& !notMoved)
                    roll = 0;
                
                //   cout << roll << endl;
                if (roll <= 0)
                    newTurn = true;
                pieceShape[stoi(movedPiece->getPlayer()->getPlayerID())][stoi(pieceID)].setPosition(x, y);

            }
            else
            {
                roll -= 6;
                newTurn = false;
                pieceShape[turn][stoi(pieceID)].setPosition(x, y);

            }

            Piece* takenPiece{};
            if (movedPiece != nullptr)
                takenPiece = Ludo.checkTake(board, movedPiece, playerCount, pieceCount, players);
            if (takenPiece != nullptr)
            {
                pair<float, float> moveToPos = Ludo.moveToInitialPos(takenPiece);
                int takenPlayerInd = stoi(takenPiece->getPlayer()->getPlayerID());
                int takenPieceInd = stoi(takenPiece->getPieceID());
                pieceShape[takenPlayerInd][takenPieceInd].setPosition(moveToPos.first, moveToPos.second);
                takenPiece->setLock(true);
            }
        }
        else if (validator == -1)
        {
            ++turn;
            newTurn = true;
            if (turn >= playerCount)
                turn = 0;
            continue;
        }

        if (movedPiece != nullptr && movedPiece->getPiecePos().second == 18)
        {
            if (pugGaiGoti(Ludo, movedPiece, pieceShape))
            {
                if (turn == 0)
                    cout << "\nRed Won"<<endl;
                else if (turn == 1)
                    cout << "\nYellow Won" << endl;
                else if (turn == 2)
                    cout << "\nGreen Won" << endl;          //For Win :D
                else if (turn == 3)
                    cout << "\nOrange Won" << endl;
                else if (turn == 4)
                    cout << "\nPurple Won" << endl;
                else
                    cout << "\nBlue Won" << endl;
                window.close();
            }
        }
        //cout << r << " " << c << endl;
        drawPieces(pieceShape, playerCount, pieceCount,characters,turn);

        if (newTurn)
        {
            ++turn;
            if (turn >= playerCount)
                turn = 0;
        }
        window.display();
    }
}
