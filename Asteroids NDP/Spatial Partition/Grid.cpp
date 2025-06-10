//
//  Grid.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 06/06/25.
//

#include "Grid.hpp"

Grid::Grid(std::list<std::shared_ptr<GameObject>>& gameObjectsInScene, PointsManager& pointsManager): collisionDetection(CollisionDetection()), gameObjectsInScene(gameObjectsInScene), pointsManager(pointsManager), asteroidSpawner(nullptr) {
    //Limpa o Grid:
    for (int x = 0; x < NUM_CELLS; x++)
    {
      for (int y = 0; y < NUM_CELLS; y++)
      {
        cells[x][y] = nullptr;
      }
    }
}

void Grid::initAsteroidSpawner(std::shared_ptr<AsteroidSpawner> spawner){
    asteroidSpawner = spawner;
}

void Grid::add(std::shared_ptr<GameObject> unit)
{
    // Determina qual célula do grid o objeto está
    // Dividir pelo tamanho de cada célula converte coordenadas do mundo em espaço da célula local. E por fim, fazer cast pra um int tira a parte fracionada pra conseguirmos o index correto.
    int cellX = (int)(unit->position.x / Grid::CELL_SIZE);
    int cellY = (int)(unit->position.y / Grid::CELL_SIZE);
    
    // Ve se nao ta fora do limite, para evitar o crash.
    if (cellX < 0 || cellX >= NUM_CELLS || cellY < 0 || cellY >= NUM_CELLS) return;
    
    // Adiciona na frente da lista pra célula que estiver, se já tem uma unidade, adiciona ela na frente dela
    unit->previous = nullptr;
    unit->next = cells[cellX][cellY];
    cells[cellX][cellY] = unit;
    
    if (unit->next != nullptr)
    {
        unit->next->previous = unit;
    }
}

void Grid::handleCollision(){
    //Note que aqui também fazemos um for dentro de um for pra checar a colisão, a diferença é que fazemos ele apenas em objetos próximos o suficiente de si, esse é o ponto dessa otimização
    for (int x = 0; x < NUM_CELLS; x++)
    {
        for (int y = 0; y < NUM_CELLS; y++)
        {
            handleCell(x,y);
        }
    }
}

void Grid::handleCell(int x, int y)
{
  std::shared_ptr<GameObject> unit = cells[x][y];
  while (unit != nullptr)
  {
    if (!unit->getIsAlive()) return;
      
    // Cuida das unidades na mesma célula.
    if (unit->next != nullptr) handleUnit(unit, unit->next);

    // Também tenta as células vizinhas.
    if (x > 0 && y > 0) handleUnit(unit, cells[x - 1][y - 1]);
    if (x > 0) handleUnit(unit, cells[x - 1][y]);
    if (y > 0) handleUnit(unit, cells[x][y - 1]);
    if (x > 0 && y < NUM_CELLS - 1)
    {
      handleUnit(unit, cells[x - 1][y + 1]);
    }

    unit = unit->next;
  }
}

void Grid::handleUnit(std::shared_ptr<GameObject> unit, std::shared_ptr<GameObject> other){
    while (other != nullptr) {
        if (other->getIsAlive() && collisionDetection.checkCollision(unit->position, other->position)) {
//            std::cout << "pegou colisao" << std::endl;
            handleAttack(unit, other);
        }
        other = other->next;
    }
}

//void checkAsteroidBulletCollision(){
//    for(auto& objectA : gameObjectsInScene){
//        if(dynamic_cast<PlayerBullet*>(objectA.get()) == nullptr) continue;
//
//        for (auto& objectB : gameObjectsInScene){
//            AsteroidGameObject* asteroidObject = dynamic_cast<AsteroidGameObject*>(objectB.get());
//            if(asteroidObject == nullptr || !asteroidObject->canBeHit()) continue;
//
//            if (collisionDetection.checkCollision(objectA->position, objectB->position)){
//                AsteroidGameObject* asteroidObject = static_cast<AsteroidGameObject*>(objectB.get());
//
//                if (asteroidObject->getAsteroidType() == SMALL){
//                    objectB->setIsAlive(false);
//                }
//                else{
//                    gameObjectsInScene.push_back(asteroidSpawner->SpawnAsteroid(SMALL,objectB->position.x,objectB->position.y));
//                    objectB->setIsAlive(false);
//                }
//
//                points += 60;
//                pointsLabel->setValue(points);
//                objectA->setIsAlive(false);
//                break;
//            }
//        }
//    }
//
//}

void Grid::handleAttack(std::shared_ptr<GameObject> unit, std::shared_ptr<GameObject> other){

    AsteroidGameObject* asteroidA = dynamic_cast<AsteroidGameObject*>(unit.get());
    AsteroidGameObject* asteroidB = dynamic_cast<AsteroidGameObject*>(other.get());

    PlayerBullet* bulletA = dynamic_cast<PlayerBullet*>(unit.get());
    PlayerBullet* bulletB = dynamic_cast<PlayerBullet*>(other.get());

    if (asteroidA && bulletB){
        destroyAsteroidAndBullet(asteroidA, bulletB);
    }
    else if (asteroidB && bulletA){
        destroyAsteroidAndBullet(asteroidB, bulletA);
    }

}

void Grid::destroyAsteroidAndBullet(AsteroidGameObject* asteroid, PlayerBullet* bullet){
    if (asteroid->getAsteroidType() == MEDIUM) {
        gameObjectsInScene.push_back(asteroidSpawner->SpawnAsteroid(SMALL,asteroid->position.x,asteroid->position.y));
    }
    asteroid->setIsAlive(false);
    pointsManager.addPoints(60);
    bullet->setIsAlive(false);
}

void Grid::checkCellChange(std::shared_ptr<GameObject> unit, float x, float y){
    // Ve em qual célula estava
    int oldCellX = (int)(unit->position.x / Grid::CELL_SIZE);
    int oldCellY = (int)(unit->position.y / Grid::CELL_SIZE);

    // Vê para qual célula vai
    int cellX = (int)(x / Grid::CELL_SIZE);
    int cellY = (int)(y / Grid::CELL_SIZE);
    
    unit->position.x = x;
    unit->position.y = y;
    
    // Se não mudou de célula, retorna
    if (oldCellX == cellX && oldCellY == cellY) return;

    // Tire ela da lista da célula antiga
    if (unit->previous != nullptr)
    {
        unit->previous->next = unit->next;
    }

    if (unit->next != nullptr)
    {
        unit->next->previous = unit->previous;
    }

    // Se é o começo da lista antiga, remove ela
    if (cells[oldCellX][oldCellY] == unit)
    {
        cells[oldCellX][oldCellY] = unit->next;
    }

    add(unit);
}
