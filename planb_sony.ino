#include <SDHCI.h>
#include <Audio.h>

SDClass theSD;
AudioClass *theAudio;

File red;
File blue;
File green;
bool ErrEnd = false;

#define sensorPin A1
#define redled 2
#define blueled 3
#define greenled 4



int sensorData;
int conv;



static void audio_attention_cb(const ErrorAttentionParam *atprm)
{
  puts("Attention!");

  if (atprm->error_code >= AS_ATTENTION_CODE_WARNING)
  {
    ErrEnd = true;
  }
}

void setup() {

  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(redled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(greenled, OUTPUT);

  theAudio = AudioClass::getInstance();

  theAudio->begin(audio_attention_cb);

 

  theAudio->setRenderingClockMode(AS_CLKMODE_NORMAL);
  
  theAudio->setPlayerMode(AS_SETPLAYER_OUTPUTDEVICE_SPHP, AS_SP_DRV_MODE_LINEOUT);
  

 



}

void loop() {


  sensorData = analogRead(sensorPin);


  conv = map(sensorData, 1000, 1, 0, 100);
  Serial.println(conv);

  if (conv > 0 && conv < 25)
  {
    digitalWrite(redled, HIGH);
    digitalWrite(blueled, LOW);
    digitalWrite(greenled, LOW);
    

  }

  if (conv > 25 && conv < 50)
  {
    digitalWrite(redled, LOW);
    digitalWrite(blueled, HIGH);
    digitalWrite(greenled, LOW);
  }

  if (conv > 50 && conv < 100)
  {
    digitalWrite(redled, LOW);
    digitalWrite(blueled, LOW);
    digitalWrite(greenled, HIGH);
    playred();
  }


}



void playred()
{

  
   err_t err = theAudio->initPlayer(AudioClass::Player0, AS_CODECTYPE_MP3, "/mnt/sd0/BIN", AS_SAMPLINGRATE_AUTO, AS_CHANNEL_STEREO);
   red = theSD.open("Sound1.mp3");
    err = theAudio->writeFrames(AudioClass::Player0, red);

      if ((err != AUDIOLIB_ECODE_OK) && (err != AUDIOLIB_ECODE_FILEEND))
    {
      printf("File Read Error! =%d\n",err);
      red.close();
      exit(1);
    }
  puts("Play!");
  theAudio->setVolume(-160);
  theAudio->startPlayer(AudioClass::Player0);  
  puts("loop!!");
err = theAudio->writeFrames(AudioClass::Player0, red);
  if (err == AUDIOLIB_ECODE_FILEEND)
    {
      printf("Main player File End!\n");
    }

  /* Show error code from player and stop */
  if (err)
    {
      printf("Main player error code: %d\n", err);
      goto stop_player;
    }

  if (ErrEnd)
    {
      printf("Error End\n");
      goto stop_player;
    }
      usleep(40000);


  /* Don't go further and continue play */
  return;

stop_player:
  sleep(1);
  theAudio->stopPlayer(AudioClass::Player0);
  red.close();
  exit(1);
}


void playblue()
{

  
   err_t err = theAudio->initPlayer(AudioClass::Player0, AS_CODECTYPE_MP3, "/mnt/sd0/BIN", AS_SAMPLINGRATE_AUTO, AS_CHANNEL_STEREO);
   blue = theSD.open("Sound2.mp3");
    err = theAudio->writeFrames(AudioClass::Player0, blue);

      if ((err != AUDIOLIB_ECODE_OK) && (err != AUDIOLIB_ECODE_FILEEND))
    {
      printf("File Read Error! =%d\n",err);
      blue.close();
      exit(1);
    }
  puts("Play!");
  theAudio->setVolume(-160);
  theAudio->startPlayer(AudioClass::Player0);  
  puts("loop!!");
err = theAudio->writeFrames(AudioClass::Player0, blue);
  if (err == AUDIOLIB_ECODE_FILEEND)
    {
      printf("Main player File End!\n");
    }

  /* Show error code from player and stop */
  if (err)
    {
      printf("Main player error code: %d\n", err);
      goto stop_player;
    }

  if (ErrEnd)
    {
      printf("Error End\n");
      goto stop_player;
    }
      usleep(40000);


  /* Don't go further and continue play */
  return;

stop_player:
  sleep(1);
  theAudio->stopPlayer(AudioClass::Player0);
  blue.close();
  exit(1);
}

void playgreen()
{

  
   err_t err = theAudio->initPlayer(AudioClass::Player0, AS_CODECTYPE_MP3, "/mnt/sd0/BIN", AS_SAMPLINGRATE_AUTO, AS_CHANNEL_STEREO);
   green = theSD.open("Sound3.mp3");
    err = theAudio->writeFrames(AudioClass::Player0, green);

      if ((err != AUDIOLIB_ECODE_OK) && (err != AUDIOLIB_ECODE_FILEEND))
    {
      printf("File Read Error! =%d\n",err);
      green.close();
      exit(1);
    }
  puts("Play!");
  theAudio->setVolume(-160);
  theAudio->startPlayer(AudioClass::Player0);  
  puts("loop!!");
err = theAudio->writeFrames(AudioClass::Player0, green);
  if (err == AUDIOLIB_ECODE_FILEEND)
    {
      printf("Main player File End!\n");
    }

  /* Show error code from player and stop */
  if (err)
    {
      printf("Main player error code: %d\n", err);
      goto stop_player;
    }

  if (ErrEnd)
    {
      printf("Error End\n");
      goto stop_player;
    }
      usleep(40000);


  /* Don't go further and continue play */
  return;

stop_player:
  sleep(1);
  theAudio->stopPlayer(AudioClass::Player0);
  green.close();
  exit(1);
}

