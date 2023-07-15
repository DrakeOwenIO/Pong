#include "game.h"



// Inititization Stuff
bool Game::Init() {

    // If renderer doesn't work return false
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return false;
    }

    // Create the window
    window = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1270, 800, 0);
    // Check that the window worked
    if (!window) {
        return false;
    }

    // Create Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_ACCELERATED);

    // Initialization of paddles
    leftPaddle = new Paddle(0);
    rightPaddle = new Paddle(1);

    // Initialize ball
    ball = new Ball;

    return true;
}

// Gameloop
void Game::GameLoop() {
    while (isRunning) {
        HandleEvents();
        Update();
        Draw();
    }
}

// *** FUNCTION DEFS ***

void Game::HandleEvents() {

    // Update the window
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }

    // Close game with escape
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }

    // Left Paddle Movement
    leftPaddle->SetDir(0);
    if (keystates[SDL_SCANCODE_W]) {
        leftPaddle->SetDir(-1);
    }
    if (keystates[SDL_SCANCODE_S]) {
        leftPaddle->SetDir(1);
    }

    // Right Paddle Movement
    rightPaddle->SetDir(0);
    if (keystates[SDL_SCANCODE_UP]) {
        rightPaddle->SetDir(-1);
    }
    if (keystates[SDL_SCANCODE_DOWN]) {
        rightPaddle->SetDir(1);
    }
}

void Game::Update() {
    leftPaddle->Update();
    rightPaddle->Update();

    ball->Update();

    if (ball->HasCollided(leftPaddle)) {
        cout << "LEFT" << endl;
        ball->InvertXVel();
    }
    if (ball->HasCollided(rightPaddle)) {
        cout << "Right" << endl;
        ball->InvertXVel();
    }
}

void Game::Draw() {
    // Make Windows
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderClear(renderer);

    // Draw Paddles
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, leftPaddle->GetRect());
    SDL_RenderFillRect(renderer, rightPaddle->GetRect());

    // Draw Ball
    SDL_SetRenderDrawColor(renderer, 40, 40, 255, 255);
    SDL_RenderFillRect(renderer, ball->GetRect());

    // Display Everything
    SDL_RenderPresent(renderer);
}

// Kill
void Game::Shutdown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}