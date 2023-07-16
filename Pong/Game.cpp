#include "game.h"

// Test commit comment

// Inititization Stuff
bool Game::Init() {

    // If renderer doesn't work return false
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
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
    if (!renderer) {
        return false;
    }

    // Create Text
    if (TTF_Init() != 0) {
        return false;
    }

    // Open audio channel
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // Initialization of paddles
    leftPaddle = new Paddle(0);
    rightPaddle = new Paddle(1);

    // Initialize ball
    ball = new Ball(this);

    // Set Font
    font = TTF_OpenFont("Assets/font.ttf", 32);

    return true;
}

void Game::SetGameStatesPending() {
    gameState = Gamestates::Pending;
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

    // Close game with escape
    if (keystates[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }

    // Changes game state from pending to playing
    if (gameState == Gamestates::Pending) {
        if (keystates[SDL_SCANCODE_SPACE]) {
            gameState = Gamestates::Playing;
        }
        return;
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
    if (gameState == Gamestates::Pending) {
        return;
    }
    
    leftPaddle->Update();
    rightPaddle->Update();

    ball->Update(leftPaddle, rightPaddle);
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

    // Print scores
    leftPaddle->showScore(renderer, font, fontColor);
    rightPaddle->showScore(renderer, font, fontColor);

    // Display Everything
    SDL_RenderPresent(renderer);
}

// Kill
void Game::Shutdown() {
    ball->Shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}