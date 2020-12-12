#ifndef FLAPPYBIRD_DEFINITIONS_HPP
#define FLAPPYBIRD_DEFINITIONS_HPP

#include <string>

const size_t SCREEN_WIDTH = 768;
const size_t SCREEN_HEIGHT = 1024;

const std::string MAIN_MENU_BACKGROUND_FILEPATH(R"(..\Resources\res\sky.png)");
const std::string GAME_BACKGROUND_FILEPATH(R"(..\Resources\res\sky.png)");
const std::string GAME_OVER_BACKGROUND_FILEPATH(R"(..\Resources\res\sky.png)");

const std::string GAME_TITLE_FILEPATH(R"(..\Resources\res\title.png)");
const std::string PLAY_BUTTON_FILEPATH(R"(..\Resources\res\PlayButton.png)");

const std::string UPPER_PIPE_FILEPATH(R"(..\Resources\res\PipeUp.png)");
const std::string LOWER_PIPE_FILEPATH(R"(..\Resources\res\PipeDown.png)");
const std::string SCORING_PIPE_FILEPATH(R"(..\Resources\res\InvisibleScoringPipe.png)");

const std::string LAND_FILEPATH(R"(..\Resources\res\land.png)");

const std::string BIRD_1_FILEPATH(R"(..\Resources\res\bird-01.png)");
const std::string BIRD_2_FILEPATH(R"(..\Resources\res\bird-02.png)");
const std::string BIRD_3_FILEPATH(R"(..\Resources\res\bird-03.png)");
const std::string BIRD_4_FILEPATH(R"(..\Resources\res\bird-04.png)");

const std::string BRONZE_MEDAL_FILEPATH(R"(..\Resources\res\Bronze-Medal.png)");
const std::string SILVER_MEDAL_FILEPATH(R"(..\Resources\res\Silver-Medal.png)");
const std::string GOLD_MEDAL_FILEPATH(R"(..\Resources\res\Gold-Medal.png)");
const std::string PLATINUM_MEDAL_FILEPATH(R"(..\Resources\res\Platinum-Medal.png)");

const std::string FLAPPY_FONT_FILEPATH(R"(..\Resources\fonts\FlappyFont.ttf)");

const std::string GAME_OVER_TITLE_FILEPATH(R"(..\Resources\res\Game-Over-Title.png)");
const std::string GAME_OVER_SCORE_FILEPATH(R"(..\Resources\res\Game-Over-Body.png)");
const std::string GAME_OVER_HIGHSCORE_FILEPATH(R"(..\Resources\highscore.txt)");

const std::string HIT_SOUND_FILEPATH(R"(..\Resources\audio\Hit.wav)");
const std::string POINT_SOUND_FILEPATH(R"(..\Resources\audio\Point.wav)");
const std::string WING_SOUND_FILEPATH(R"(..\Resources\audio\Wing.wav)");

const float PIPE_MOVEMENT_SPEED = 200.0f;

const double BIRD_ANIMATION_DURATION = 0.4f;

const float GRAVITY = 350.0f;
const float FLYING_SPEED = 350.0f;
const double FLYING_DURATION = 0.25;

const float ROTATION_SPEED = 100.0f;
const float MAX_ROTATION_VALUE = 25.0f;

const double FLASH_SPEED = 1500.0f;

const double TIME_BEFORE_GAME_OVER = 1.0;

enum class BIRD_STATE
{
  STILL = 1,
  FAILING,
  FLYING
};

enum class GAME_STATE
{
  READY,
  PLAYING,
  GAME_OVER
};

enum class MEDAL_SCORE
{
  BRONZE = 0,
  SILVER = 5,
  GOLD = 25,
  PLATINUM = 100
};

#endif //FLAPPYBIRD_DEFINITIONS_HPP
