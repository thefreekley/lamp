#define CLK 7
#define DT 11
#define SW 3
#define p_1 5
#define p_2 9
#define p_3 6

#define top 2872
#define bottom 3896
#define right 1848
#define left 824
#define OK 2672

#define button1 464 /// на пульті це від ліва до права почінаючі з верху  pramouglolniki            
#define button2 4048
#define button3 2640
#define button4 24101
#define button5 112

#define right_plus 144
#define right_minus 2192
#define green_b 2704 

#define left_plus 1168
#define left_minus 3216
#define press_buton 4294967295


#define round1 16
#define round2 2064
#define round3 1040
#define round4 3088
#define round5 528
#define round6 2576
#define round7 1552
#define round8 3600
#define round9 272
#define round10 2960
#define round11 2320
#define round12 1488

#define top_button_left 656
#define top_button_right 2704



#include "GyverEncoder.h"

Encoder enc1(CLK, DT, SW);
#include <IRremote.h>

IRrecv irrecv(8);
decode_results results;
 
byte colors_[10][5] {
  {250, 250, 250}, // t0 p0
  {0, 0, 250}, // t0 p1
  {100, 0, 250}, //t1 p1 0,100,250
  {0, 250, 250}, // t0 p0
  {0, 250, 0}, //t1 p2 250,0,0
  {250, 100, 0}, //t0 t3
  {250, 250, 0}, //t0 p3
  {250, 0, 0}, //t0 p2
  {250, 0, 250}, //t1 p0 0,250,250
};

  static int periods; // періуд зміни режимаж
const int value_max = 250; // максимальный шим сигнал
int clr_1, clr_2, clr_3; // кольори з цветами
int times; // періуд зміни кольора
int vision;
unsigned long aceleration;
int influence;
unsigned int influence_sraka;
unsigned long time_press_1;
unsigned long time_press_2;
boolean kerob;
boolean flag_1;
boolean flag_2;
boolean flag_3;
int mode;
boolean flag_4;
boolean IR_flag_right;
boolean IR_flag_left;
boolean  IR_flag_OK;
boolean start_rb;
volatile unsigned int point;
//int alpha;
boolean color_musik;
int brake;
boolean start_mus;
int mode_dance;
byte past_clr_1;
byte past_clr_2;
byte past_clr_3;
byte vision_false;
boolean start_mus3;
boolean sound_off;
double speed_of_flash;
boolean speed_IR_plus;
boolean speed_IR_minus;
byte mode_dinamic;
//int SPD_cb;
boolean left_plus_IR;
boolean left_minus_IR;
int speed_dinamic[10];
boolean roundF[10];
boolean flag_dst1;
boolean flag_dst2;
boolean flag_dst3;
  int clr_fuck1;
  int clr_fuck2;
  int clr_fuck3;
  int old_vision;
void setup() {
  clr_fuck1=250;
  clr_fuck2=250;
  clr_fuck3=250;
  speed_of_flash = 0.001;
  past_clr_1 = 250;
  past_clr_2 = 250;
  past_clr_3 = 250;
  brake = 10;
  speed_dinamic[0] = 15;
  speed_dinamic[1] = 15;
  speed_dinamic[2] = 15;
 //Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP);
 // Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(0, sound, RISING);
  irrecv.enableIRIn();
  enc1.setType(TYPE2);    // тип энкодера TYPE1 одношаговый, TYPE2 двухшаговый. Если ваш энкодер работает странно, смените тип
  clr_1 = value_max; // клр1
  clr_2 = value_max; // клр2
  clr_3 = value_max; // клр3
  
  //pinMode(A0, INPUT_PULLUP);
  randomSeed(analogRead(0));
analogWrite(10,255);
delay(50);
analogWrite(10,3);
}

void loop() {

 // Serial.println(vision);
  // обязательная функция отработки. Должна постоянно опрашиваться
  enc1.tick();
  if (enc1.isRightH());// if(bloom==0)lvlLight(1);
  if (enc1.isLeftH()); //if(bloom==0) lvlLight(); // krutish i zaderzuesh zmenshuetsa yarkast
  double_click(); //flag_1 як знак дворазового нажимання //flag_2 click одноразове //flag 3 press_ довге

  if (mode != 2 && sound_off == 0)sound_sum(0); //  flag_2 як знак звука
  IR_proces(); // IR_flag_left буде як перемічка в лєво, IR_flag_left в право
  //switch (mode)
  //if(flag_1)Serial.println("DOUBLE");
  //if(flag_2)Serial.println("CLICK");
  //if(flag_3)Serial.println("PRESS");

  if (flag_2 ) {
    if (mode > 4)mode = 0;
    else mode++;
    if (mode == 0) {
      clr_1 = past_clr_1;
      clr_2 = past_clr_2;
      clr_3 = past_clr_3;
    } // запамьятовує кольора які були до того і віддає них
    mode_dinamic = 0;
    mode_dance = 0;
  }
  switch (mode) {
    case 0:
      
      for (int i = 0; i < 9; i++) {

        if (roundF[i] == 1) {
          switch (i){
            case 0: clr_1=250; clr_2=250; clr_3=250; periods=0; times=0; break;
            case 1: clr_1=0; clr_2=0; clr_3=250; periods=1; times=0; break;
            case 2: clr_1=100; clr_2=0; clr_3=250; periods=1; times=1; break;
            case 3: clr_1=0; clr_2=250; clr_3=250; periods=0; times=0; break;
            case 4: clr_1=0; clr_2=250; clr_3=0; periods=2; times=1; break;
            case 5: clr_1=250; clr_2=100; clr_3=0; periods=3; times=0; break;
            case 6: clr_1=250; clr_2=250; clr_3=0; periods=3; times=0; break;
            case 7: clr_1=250; clr_2=0; clr_3=0; periods=2; times=0; break;
            case 8: clr_1=250; clr_2=0; clr_3=250; periods=0; times=1; break;
           
          }
          switch(times){
    case 0: clr_fuck1=clr_1; clr_fuck2=clr_2; clr_fuck3=clr_3;  break;
    case 1: clr_fuck1=clr_2; clr_fuck2=clr_1; clr_fuck3=clr_3; break;
    case 2: clr_fuck1=clr_3; clr_fuck2=clr_1; clr_fuck3=clr_2; break;
    case 3: clr_fuck1=clr_2; clr_fuck2=clr_3; clr_fuck3=clr_1; break;
    case 4: clr_fuck1=clr_2; clr_fuck2=clr_3; clr_fuck3=clr_1; break;
    case 5: clr_fuck1=clr_3; clr_fuck2=clr_2; clr_fuck3=clr_1; break;

  }
        }
      }
      static boolean kr_1;
      static boolean kr_2;
      static boolean kr_3;
       static unsigned long go_over;
     //static int val_go;
    
      if(flag_dst3==1){ kr_3=!kr_3; kr_1=0; kr_2=0;}
      if(flag_dst2==1){ kr_2=!kr_2;  kr_1=0; kr_3=0;}
      if(flag_dst1==1){ kr_1=!kr_1; kr_2=0;kr_3=0;}
   
/*
 
      Serial.print(clr_1);
      Serial.print("  1  ");
      Serial.print(clr_2);
      Serial.print("  2  ");
      Serial.print(clr_3);
      Serial.print("  3  ");
      Serial.print(times);
      Serial.print("  times  ");
      Serial.print(periods);
      Serial.println("  periods  "); 
     */
     
      if (enc1.isRight() || IR_flag_right)  enc_reg(1);
      if (enc1.isLeft() || IR_flag_left) enc_reg(0);
      if (flag_3)bloom();
     
      
      start_rb = 0;

      if (flag_1 == 1 || left_plus_IR)lvlLight(3);////////////////////////
      if (left_minus_IR) lvlLight(4);
      if (flag_4 == 1)lvlLight(2);
      
     if(kr_2==0 && kr_3==0 && kr_1==0){
      analog_wr(clr_1,clr_2,clr_3);
     }
 
   
    static unsigned long times_bring;
     static double  val_14=0.01;
    #define ablako 0.01
     static boolean aby;
     if( kr_3==1){
    if(IR_flag_OK)val_14=ablako;
        if (speed_IR_plus) {
        val_14+= ablako;
      }
      if (speed_IR_minus) {
        // Serial.println(alpha);
        if (val_14>ablako)val_14 -= ablako;
        else val_14= ablako;
      }
      if(millis()-times_bring>val_14){
        aby=!aby;
        times_bring=millis();
      }
      if(aby==1)analog_wr(clr_1,clr_2,clr_3);
      else analog_wr(0,0,0);
      
      
    }
    static int clr_1_x2;
    static int clr_2_x2;
    static int clr_3_x2;

    static int sum_x2;
    static unsigned long time_x2;
    static boolean change_x2;
    static int speed_x2=100;
    if(kr_2==1){
      if(IR_flag_OK)speed_x2=100;
        if (speed_IR_plus) {
        speed_x2+= 5;
      }
      
      if (speed_IR_minus) {
        // Serial.println(alpha);
        if (speed_x2>5)speed_x2-=5;
        else speed_x2=5 ;
      }
      
      if(millis()-time_x2>speed_x2/10){
        if(sum_x2>100)change_x2=1;
        if(sum_x2<2)change_x2=0;
        if(change_x2==0)sum_x2++;
        else sum_x2--;
         time_x2=millis();
      }
      clr_1_x2=(clr_1/100)*sum_x2;
      clr_2_x2=(clr_2/100)*sum_x2;
      clr_3_x2=(clr_3/100)*sum_x2;
      
            analog_wr(clr_1_x2,clr_2_x2,clr_3_x2);
    }

     static int clr_1_x1;
    static int clr_2_x1;
    static int clr_3_x1;

    static int sum_x1;
    static unsigned long time_x1;
    static boolean change_x1;
    static int speed_x1=100;
    
    if(kr_1==1){
      if(IR_flag_OK)speed_x1=100;
        if (speed_IR_plus) {
        speed_x1+= 5;
      }
      
      if (speed_IR_minus) {
        // Serial.println(alpha);
        if (speed_x1>5)speed_x1-=5;
        else speed_x1=5 ;
      }
      if(millis()-time_x1>speed_x1/10){
        if(sum_x1>100)change_x1=1;
        if(sum_x1<75){change_x1=0;}
        if(change_x1==0)sum_x1++;
        else sum_x1--;
         time_x1=millis();
      }
      
      clr_1_x1=((clr_1)/100)*sum_x1;
      clr_2_x1=((clr_2)/100)*sum_x1;
      clr_3_x1=((clr_3)/100)*sum_x1;
      
   
      
            analog_wr(clr_1_x1,clr_2_x1,clr_3_x1);
    }
    
      break;
    case 1: /////////////////////////////////////////////////////////////////1111111111111111111111111111111111111111111111111111111111111
           static boolean kr2_1;
      static boolean kr2_2;
      static boolean kr2_3;
      if(flag_dst3==1){ kr2_3=!kr2_3; kr2_1=0; kr2_2=0;  clr_1=0; clr_2=0; clr_2=0;}
      if(flag_dst2==1){ kr2_2=!kr2_2;  kr2_1=0; kr2_3=0; clr_1=0; clr_2=0; clr_2=0;}
      if(flag_dst1==1){ kr2_1=!kr2_1; kr2_2=0;kr2_3=0; clr_1=0; clr_2=0; clr_2=0;}

          if (left_plus_IR)lvlLight(3);
      if (left_minus_IR) lvlLight(4);
      if (enc1.isRightH()) lvlLight(3);
      if (enc1.isRightH()) lvlLight(4);
      if (flag_4 == 1)lvlLight(2);
      
         if(kr2_2==0 && kr2_3==0 && kr2_1==0){
      if (enc1.isRight() || speed_IR_plus) {
        //Serial.println(alpha);
        speed_dinamic[mode_dinamic] += 5;
      }
      if (enc1.isLeft() || speed_IR_minus) {
        // Serial.println(alpha);
        if (speed_dinamic[mode_dinamic] > 6)speed_dinamic[mode_dinamic] -= 5;
        else speed_dinamic[mode_dinamic] = 5;
      }
      if (flag_1 == 1 || IR_flag_right) {
        if (mode_dinamic < 8) mode_dinamic++;
        else mode_dinamic = 0;

      }

      if (IR_flag_left) {
        if (mode_dinamic >= 0) mode_dinamic--;
        else mode_dinamic = 4;

      }
      // Serial.println(mode_dinamic);
      switch (mode_dinamic) {
        case 0: rainbow(); break;
        case 1: color_blink(); break;
        case 2:  New_Year_blink(); break;
        case 3:  fire(); break;
        case 4: burn(0); break;
        case 5:burn(1); break;
        case 6:burn(2); break;
        case 7: lol();break;
      }
         }
         
          if(kr2_1==1)change_rainbow(0);
          if (kr2_2==1)change_rainbow(1);
          if(kr2_3==1)change_rainbow(2);
         
         
      break;
    case 2: ///////////////////////////////////////////////////////////////
      //  Serial.println(speed_of_flash);
      sound_sum(1);
      color_branch();
      if (enc1.isRight() || speed_IR_plus)brake += 5;

      if (enc1.isLeft() || speed_IR_minus) {
        if (brake > 2)brake -= 5;
        else brake = 1;
      }

      if (flag_1 == 1 || IR_flag_right) {
        if (mode_dance < 4) mode_dance++;
        else mode_dance = 0;
      }

      if (IR_flag_left) {
        if (mode_dance >= 0) mode_dance--;
        else mode_dance = 4;
      }

      if (left_plus_IR)lvlLight(0);
      if (left_minus_IR) lvlLight(1);
      if (enc1.isRight() && flag_3) lvlLight(3);
      if (enc1.isRight() && flag_3) lvlLight(4);

      break;
  }
}
void burn(byte kent){
    static int clr_1_x1;
    static int clr_2_x1;
    static int clr_3_x1;

    static int sum_x1;
    static unsigned long time_x1;
    static boolean change_x1;
    static int speed_x1=100;
    
    if(IR_flag_OK)speed_x1=100;
        if (speed_IR_plus) {
        speed_x1+= 5;
      }
      
      if (speed_IR_minus) {
        // Serial.println(alpha);
        if (speed_x1>5)speed_x1-=5;
        else speed_x1=5 ;
      }
      if(millis()-time_x1>((speed_x1*speed_x1)/500)){
        if(sum_x1>254)change_x1=1;
        if(sum_x1<10){change_x1=0;}
        if(change_x1==0)sum_x1++;
        else sum_x1--;
         time_x1=millis();
      }
      //Serial.println(sum_x1);
      switch(kent){
           case 0: analog_wr(250,sum_x1,0); break;
           case 1: analog_wr(250,sum_x1,250); break;
           case 2: analog_wr(0,sum_x1,250); break;
      }
}
void change_rainbow(byte debil_chok){
   int num_colors[10];
   static boolean colors_0[10];
    int changes_0 = 0;
  //  static int link_0;
    static unsigned long abq;
     static int speed_x1=500;
     static unsigned long time_nyb1;
     static int change_nyb=0;
    for (int i = 0; i < 10; i++) {
    num_colors[i] = 0;
  }
    
    for (int i = 0; i < 9; i++) {
      if (roundF[i] == 1) {
        if (colors_0[i + 1] == 0)colors_0[i + 1] = 1;
        else colors_0[i + 1] = 0;
      }

    }
    for (int i = 1; i <= 9; i++) {
      if (colors_0[i] == 1) {
        changes_0++;
        num_colors[changes_0] = i;
      }
    }
    if(IR_flag_OK){
      for(int i=0;i<10;i++){
        colors_0[i]=0;
        num_colors[i]=0;
      }  
    changes_0=0;
    change_nyb=0;
    
    clr_1=0;
    clr_2=0;
    clr_2=0;
    }   
  
    
//          clr_1 = colors_[num_colors[link_0] - 1][0];
       //   clr_2 = colors_[num_colors[link_0] - 1][1];
      //    clr_3 = colors_[num_colors[link_0] - 1][2]; 
    
  if(debil_chok==0){

    
//Serial.print(speed_x1);
//Serial.println("   speed");
     if(IR_flag_OK)speed_x1=500;
        if (speed_IR_plus)speed_x1+= 50;  
      if (speed_IR_minus) {
        if (speed_x1>50)speed_x1-=50;
        else speed_x1=50;
      }
      
    if (millis() - time_nyb1 > speed_x1) {
    if (change_nyb > changes_0-1)change_nyb = 1;
    else change_nyb++;
    time_nyb1 = millis();
  }     if(change_nyb>0){
          clr_1 = colors_[num_colors[change_nyb]-1][0];
          clr_2 = colors_[num_colors[change_nyb]-1][1];
          clr_3 = colors_[num_colors[change_nyb]-1][2]; 
  analog_wr(clr_1,clr_2,clr_3);
  
  }
  else  analog_wr(0,0,0);
  
  }
  else if(debil_chok==1){
    static int speed_x2=500;
    static unsigned long obsolete;
    static int impact=-1;
    static int change_nyb1;
    static boolean change_impact;
    
       if(IR_flag_OK){speed_x2=500;change_nyb1=0;}
        if (speed_IR_plus)speed_x2+= 10+speed_x2/10;  
      if (speed_IR_minus) {
        if (speed_x2>50)speed_x2-=10+speed_x2/10;
        else speed_x2=10;
      }
      
  static int true_friends;
  if(millis()-obsolete>speed_x2/1000){
    if(impact<1)change_impact=0;
    if(impact>=255)change_impact=1;
    if(change_impact==1){
      impact--;
    }
    else {
      impact++;
    }
    if(impact==0)true_friends=0;
    else true_friends++;
    if(true_friends==509){
      
        if (change_nyb1 > changes_0-1)change_nyb1 = 1;
    else change_nyb1++;
    }
    
    
    
     obsolete=millis();
     //Serial.println(speed_x2);
  }
  //Serial.println(speed_x2);
 
  if(change_nyb1>0){
          clr_1 = colors_[num_colors[change_nyb1]-1][0];
          clr_2 = colors_[num_colors[change_nyb1]-1][1];
          clr_3 = colors_[num_colors[change_nyb1]-1][2]; 
  analog_wr(map(impact,0,255,0,clr_1),map(impact,0,255,0,clr_2),map(impact,0,255,0,clr_3));
  
  }
  
  }
   if(debil_chok==2){
    static unsigned int speed_x3=500;
    static unsigned long chas_pik;
    static int change_nyb2;
      if(IR_flag_OK){speed_x3=500;change_nyb2=0; clr_1=0;clr_2=0;clr_3=0;}
        if (speed_IR_plus)speed_x3+= 10+speed_x3/10;  
      if (speed_IR_minus) {
        if (speed_x3>50)speed_x3-=10+speed_x3/10;
        else speed_x3=10;
      }
      
    if(millis()-chas_pik>speed_x3/1000){
      if(clr_1==colors_[num_colors[change_nyb2]-1][0] && clr_2==colors_[num_colors[change_nyb2]-1][1] && clr_3==colors_[num_colors[change_nyb2]-1][2]){
              if (change_nyb2 > changes_0-1)change_nyb2 = 1;
    else change_nyb2++;
      }
      else{
      if(clr_1>colors_[num_colors[change_nyb2]-1][0])clr_1--;
      if (clr_1<colors_[num_colors[change_nyb2]-1][0])clr_1++;

      if(clr_2>colors_[num_colors[change_nyb2]-1][1])clr_2--;
      if (clr_2<colors_[num_colors[change_nyb2]-1][1])clr_2++;

      if(clr_3>colors_[num_colors[change_nyb2]-1][2])clr_3--;
      if (clr_3<colors_[num_colors[change_nyb2]-1][2])clr_3++;
      }
      
    
      chas_pik=millis();
    /*Serial.print(clr_1);
    Serial.print("      ");
    Serial.print(clr_2);
    Serial.print("      ");
    Serial.print(clr_3);
    Serial.print("      ");
    Serial.print(change_nyb2);
    Serial.println("       ");
    */
    }

    
    
    if(change_nyb2>0){
      analog_wr(clr_1,clr_2,clr_3);
      
    }
   }
}
void lol(){
  static unsigned long time_fr;
     static int speed_x4=1;
      
    if(IR_flag_OK)speed_x4=1;
        if (speed_IR_plus) {
        speed_x4+= 1;
      }
      
      if (speed_IR_minus) {
        // Serial.println(alpha);
        if (speed_x4>1)speed_x4-=1;
        else speed_x4=1 ;
      }
      static int bloa11;
  if(millis()-time_fr>speed_x4){
    if(bloa11<9)bloa11++;
    else bloa11=0;
    time_fr=millis();
  }
   analog_wr(colors_[bloa11][0], colors_[bloa11][1], colors_[bloa11][2]);
}
void fire() {
  static unsigned long time_fr;
     static int speed_x4=20;
    
    if(IR_flag_OK)speed_x4=20;
        if (speed_IR_plus) {
        speed_x4+= 5;
      }
      
      if (speed_IR_minus) {
        // Serial.println(alpha);
        if (speed_x4>5)speed_x4-=5;
        else speed_x4=5 ;
      }
  if (millis() - time_fr > random(speed_x4, 50+speed_x4)) {
    clr_2 = random(0, 100);
    time_fr = millis();
  }
  analog_wr(255, clr_2, 0);
}
void color_blink() {
  static unsigned long time_cb;
  static int develop;
  static boolean rise;
  static int chang_cb;
  // peremenna !-! SPD_cb
  if (millis() - time_cb > speed_dinamic[1] / 30) {
    if (develop > 253)rise = 1;
    if (develop <= 0) {
      rise = 0;
      if (chang_cb > 7)chang_cb = 0;
      else chang_cb++;

    }
    if (rise == 0)develop++;
    else develop--;
    time_cb = millis();
  }
 // if(
  clr_1 = map(develop, 0, 255, 0, colors_[chang_cb][0]);
  clr_2 = map(develop, 0, 255, 0, colors_[chang_cb][1]);
  clr_3 = map(develop, 0, 255, 0, colors_[chang_cb][2]);

  analog_wr(clr_1, clr_2, clr_3);

}
////////////////////////////////////////////////////////////////////////////////////////////////
void color_branch() {
  static int chang_dance;
  byte random_bla1;
  byte random_bla;
  int change_dance_0;
  static boolean colors_0[10];
  int num_colors[10];
  int changes_0 = 0;
  static unsigned long abq;
  static int link_0 = 1;
  for (int i = 0; i < 10; i++) {
    num_colors[i] = 0;
  }
  if (start_mus == 0) {
    clr_1 = 0;
    clr_2 = 0;
    clr_3 = 0;
    vision = 0;
  }
   if(IR_flag_OK)brake=10;
  start_mus = 1;
  if (mode_dance == 0) {
    for (int i = 0; i < 9; i++) {
      if (roundF[i] == 1) {
        if (colors_0[i + 1] == 0)colors_0[i + 1] = 1;
        else colors_0[i + 1] = 0;
      }

    }
    for (int i = 1; i <= 9; i++) {
      if (colors_0[i] == 1) {
        changes_0++;
        num_colors[changes_0] = i;
      }
    }
    if(IR_flag_OK){
      for(int i=0;i<10;i++){
        colors_0[i]=0;
        num_colors[i];
      }  
    changes_0=0;
    link_0 = 1;
    clr_1=0;
    clr_2=0;
    clr_2=0;
    }   
  }
  /*if(colors_0[0]==1)num_colors[changes]=0;
    if(colors_0[1]==1)num_colors[changes]=1;
    if(colors_0[2]==1)num_colors[changes]=2;
    if(colors_0[3]==1)num_colors[changes]=3;
    if(colors_0[4]==1)num_colors[changes]=4;
    if(colors_0[5]==1)num_colors[changes]=5;
    if(colors_0[6]==1)num_colors[changes]=6;
    if(colors_0[7]==1)num_colors[changes]=7;
    if(colors_0[8]==1)num_colors[changes]=8; */
  /*if(millis()-abq>1000){
    // for(int i=0;i<=changes_0;i++){

    for(int i=1;i<=9;i++){
    Serial.print(i);
    Serial.print("    ");
    Serial.println(num_colors[i]);
    }
    Serial.println("_________");
    abq=millis();
    }*/

  if (color_musik) {
    //Serial.println(changes_0);
    switch (mode_dance) {
      case 0:
        if (changes_0 > 0) {
          if (link_0 < changes_0 && changes_0 >= 0)link_0++;
          else link_0 = 1;

          clr_1 = colors_[num_colors[link_0] - 1][0];
          clr_2 = colors_[num_colors[link_0] - 1][1];
          clr_3 = colors_[num_colors[link_0] - 1][2];
        }
        //Serial.println(brake);
        break;
      case 1:
        if (chang_dance < 3)chang_dance++;
        else chang_dance = 0;
        if (chang_dance == 0) {
          clr_1 = 255;
          clr_2 = 255;
          clr_3 = 255;
        }
        else if (chang_dance == 1) {
          clr_1 = 255;
          clr_2 = 0;
          clr_3 = 0;
        }
        else  {
          clr_1 = 255;
          clr_2 = 0;
          clr_3 = 0;
        }
        break;
      case 2:
        random_bla1 = random(0, 8);
        clr_1 = colors_[random_bla1][0];
        clr_2 = colors_[random_bla1][1];
        clr_3 = colors_[random_bla1][2];

        break;
      case 3:

        random_bla1 = random(0, 8);
        clr_1 = colors_[random_bla1][0];
        clr_2 = colors_[random_bla1][1];
        clr_3 = colors_[random_bla1][2];

        break;
      case 4:
        if (chang_dance < 3)chang_dance++;
        else chang_dance = 0;
        if (chang_dance == 0) {
          clr_1 = 255;
          clr_2 = 255;
          clr_3 = 255;
        }
        else if (chang_dance == 1) {
          clr_1 = 255;
          clr_2 = 0;
          clr_3 = 0;
        }
        else  {
          clr_1 = 255;
          clr_2 = 0;
          clr_3 = 0;
        }
        break;

    }
    if (mode_dance == 3 || mode_dance == 4) {
      analog_wr(0, 0, 0);
      delay(brake / 2);
    }
    else {
      analog_wr(clr_1, clr_2, clr_3);
      delay(brake);
    }

  }
  else {
    if (mode_dance == 3 || mode_dance == 4)analog_wr(clr_1, clr_2, clr_3);
    else {
      analog_wr(0, 0, 0);
    }
  }
  //Serial.println(mode_dance);
}
void New_Year_blink() {
  static unsigned long time_nyb;
  static int change_nyb;
  if (millis() - time_nyb > speed_dinamic[2] * 30) {
    if (change_nyb > 7)change_nyb = 0;
    else change_nyb++;
    time_nyb = millis();
  }
  clr_1 = colors_[change_nyb][0];
  clr_2 = colors_[change_nyb][1];
  clr_3 = colors_[change_nyb][2];
  analog_wr(clr_1, clr_2, clr_3);
}
void rainbow() {

  static int changing = 0;
  static boolean ch_rb;
  static int develop;
  static unsigned long times_rb;

  if (millis() - times_rb > speed_dinamic[0] / 30) {
    if (develop < 255 )develop++;
    else {
      develop = 0;

      if (changing > 7)changing = 1;
      else changing++;
      delay(50);
    }
    times_rb = millis();
    /*Serial.print(clr_1);
      Serial.print("                      ");
      Serial.print(clr_2);
      Serial.print("                      ");
      Serial.print(clr_3);
      Serial.print("                    ");
      Serial.print(changing);
      Serial.print("                    ");
      Serial.println("");

    */
  }

  switch (changing) {
    case 0:  //clr_1- krasniy //clr_2-zeleniy// clr_3 blue /// проблема в том шо періуд подьйома і падєнія робить конфуз між конфігураціями // ще з часом броблема
      clr_1 = develop; // червоний
      clr_2 = 0;
      clr_3 = 0;
      break;
    case 1:
      clr_1 = 255;
      clr_3 = 0;
      clr_2 = map(develop, 0, 255, 0, 153); // orang
      break;
    case 2:
      clr_1 = 255;
      clr_3 = 0;
      clr_2 = 153 + map(develop, 0, 255, 0, 102); //yellow
      break;
    case 3:
      clr_1 = 255 - develop; // green
      clr_2 = 255;
      clr_3 = 0;
      break;
    case 4:
      clr_3 = develop; //blue_light
      clr_2 = 255;
      clr_1 = 0;
      break;
    case 5:
      clr_1 = 0;
      clr_2 = 255 - develop; // blue;
      clr_3 = 255;
      break;
    case 6:
      clr_1 = map(develop, 0, 255, 0, 102); //porpure
      clr_2 = 0;
      clr_3 = 255;
      break;
    case 7:
      clr_1 = 102 + map(develop, 0, 255, 0, 102);
      clr_3 = 255 - develop;
      clr_2 = 0;
      break;
  }
  analog_wr(clr_1, clr_2, clr_3);
}
void  IR_proces() {
  IR_flag_left = 0;
  IR_flag_right = 0;
  IR_flag_OK = 0;
  speed_IR_plus = 0;
  speed_IR_minus = 0;
  left_minus_IR = 0;
  left_plus_IR = 0;
  flag_dst3=0;
  flag_dst2=0;
  flag_dst1=0;
  for (int i = 0; i < 9; i++) {
    roundF[i] = 0;
  }
  static int last_click_button;
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    switch (results.value) {
      case left_minus:  left_plus_IR = 1; last_click_button=1; break;
      case left_plus: left_minus_IR = 1; last_click_button=2; break;
      case right_minus: IR_flag_left = 1; last_click_button=3; break;
      case right_plus: IR_flag_right = 1; last_click_button=4; break;
      case OK: IR_flag_OK = 1; break;
      case button1: mode = 0; clr_1 = past_clr_1; clr_2 = past_clr_2; clr_3 = past_clr_3;  break;
      case button2: mode = 1; break;
      case button3: mode = 2; break;
      case button4: speed_IR_minus = 1; last_click_button=5; break;
      case button5: speed_IR_plus = 1; last_click_button=6; break;
      case round1: roundF[0] = 1; break;
      case round2: roundF[1] = 1; break;
      case round3: roundF[2] = 1; break;
      case round4: roundF[3] = 1; break;
      case round5: roundF[4] = 1; break;
      case round6: roundF[5] = 1; break;
      case round7: roundF[6] = 1; break;
      case round8: roundF[7] = 1; break;
      case round9: roundF[8] = 1; break;
      case round10: flag_dst1=1; break;
      case round11:flag_dst2=1; break;
      case round12:flag_dst3=1; break;
      case press_buton:
          switch(last_click_button){
         //   Serial.println(last_click_button);
            case 1: left_plus_IR=1; break;
            case 2: left_minus_IR=1; break;
            case 3: IR_flag_left = 1; break;
            case 4: IR_flag_right = 1; break;
            case 5: speed_IR_minus = 1; break;
            case 6: speed_IR_plus  = 1; break;
          }
      break;
     // case green_b:resetFunc(); break;
      case top_button_left:
        if (sound_off == 1)sound_off = 0;
        else sound_off = 1;
        break;
    }
    analogWrite(10,255);
    delay(50);
    analogWrite(10,3);
    irrecv.resume();
  }
}

void sound_sum(boolean gol) {
  if (gol == 0) {
    flag_4 = 0;
    if (point > 65) {
      flag_4 = 1;
      point = 0;
       if (vision <100){
       
        old_vision=vision;
        } 

    }
  }
  else {
    color_musik = 0;
    if (point > brake) {
      color_musik = 1;
      point = 0;
    }
  }
}

void sound() {
  point++;
}
void double_click() {
  static boolean flag_false;
  static boolean fake;
  flag_1 = 0;
  flag_2 = 0;
  flag_3 = 0;
  enc1.tick();
  if (enc1.isPress()) {

    if (kerob == 0) {
      time_press_1 = millis();
      kerob = 1;

    }
    else {
      time_press_2 = millis();
      if (time_press_2 - time_press_1 < 500) {
        flag_1 = 1;
        fake = 1;    // це карочь через те шо флаг фалсе ливається тількі в условії після 500, то треба удалить шум першого нажиму якій сохранився в флаг фалсе.
      }
    }
    if (flag_1 == 0)flag_false = 1;
  }

  if (digitalRead(SW)) {
    influence = 0;
    influence_sraka = 0;
  }
  if (enc1.isHold()) {

    if (sraka()) {

      fake = 1;
      flag_3 = 1;
    }
  }

  if (millis() - time_press_1 > 500 && digitalRead(SW) == 1) {
    if (fake == 1)flag_false = 0; // процес очіщення перемєнной після того як перший клік нафлудив
    fake = 0;
    time_press_2 = 0;
    time_press_1 = 0;
    kerob = 0;
    if (flag_false == 1) {
      flag_2 = 1;
      flag_false = 0;
    }

  }

}

////melki peremenni
int sraka() {
  static unsigned long bla;
  influence_sraka++;
  if (influence_sraka < 2)bla = millis();
  if (millis() - bla > 1000)return 1;
  else return 0;
}
void bloom() {
  //static unsigned long t1;
  static unsigned long t2;


  if (millis() - t2 > 20) {
    enc_reg(1);
    t2 = millis();
  }

  //Serial.println(v_max-influence);
}

/////////////111melki_peremenni
void enc_reg(boolean sign) {
  

  const int value_change = 10; // як бистро шим міняється
 
  switch (periods) {
    case 0:
      if (sign == 1) {
        if (clr_fuck1 <= 0) periods = 1;
        else clr_fuck1 -= value_change;
      }
      if (sign == 0) {
        if (clr_fuck1 >= value_max) {
          if (times <= 0)times = 5;
          else times--;
          periods = 4;
        }
        else clr_fuck1 += value_change;
      }
      break;
    case 1:
      if (sign == 1) {
        if (clr_fuck2 <= 0) periods = 2;
        else clr_fuck2 -= value_change;
      }
      if (sign == 0) {
        if (clr_fuck2 >= value_max) periods = 0;
        else clr_fuck2 += value_change;
      }
      break;
    case 2:
      if (sign == 1) {
        if (clr_fuck3 <= 0) periods = 3;
        else {
          clr_fuck3 -= value_change;
          clr_fuck1 += value_change;
        }
      }
      if (sign == 0) {
        if (clr_fuck3 >= value_max) periods = 1;
        else {
          clr_fuck3 += value_change;
          clr_fuck1 -= value_change;
        }
      }
      break;
    case 3:
      if (sign == 1) {
        if (clr_fuck2 >= value_max) periods = 4;
        else clr_fuck2 += value_change;
      }
      if (sign == 0) {
        if (clr_fuck2 <= 0) periods = 2;
        else clr_fuck2 -= value_change;
      }
      break;
    case 4:
      if (sign == 1) {
        if (clr_fuck3 >= value_max) {
          if (times >= 5)times = 0;
          else times++;
          periods = 0;
        }
        else {
          clr_fuck3 += value_change;
          //   clr_fuck1-=value_change;

        }
      }
      if (sign == 0) {
        if (clr_fuck3 <= 0) periods = 3;
        else {
          clr_fuck3 -= value_change;
          //clr_fuck1+=value_change;
        }
      }

      break;

  }
  switch(times){
    case 0: clr_1=clr_fuck1; clr_2=clr_fuck2; clr_3=clr_fuck3;  break;
    case 1: clr_1=clr_fuck2; clr_2=clr_fuck1; clr_3=clr_fuck3; break;
    case 2: clr_1=clr_fuck3; clr_2=clr_fuck1; clr_3=clr_fuck2; break;
    case 3: clr_1=clr_fuck2; clr_2=clr_fuck3; clr_3=clr_fuck1; break;
    case 4: clr_1=clr_fuck2; clr_2=clr_fuck3; clr_3=clr_fuck1; break;
    case 5: clr_1=clr_fuck3; clr_2=clr_fuck2; clr_3=clr_fuck1; break;

  }
   past_clr_1=clr_1;
   past_clr_2=clr_2;
   past_clr_3=clr_3;
}
/*void light( int times) {
  switch (times) {
    case 0: analog_wr(clr_1, clr_2, clr_3); break;
    case 1: analog_wr(clr_2, clr_1, clr_3); break;
    case 2: analog_wr(clr_3, clr_1, clr_2); break;
    case 3: analog_wr(clr_2, clr_3, clr_1); break;
    case 4: analog_wr(clr_2, clr_3, clr_1); break;
    case 5: analog_wr(clr_3, clr_2, clr_1); break;

  }
}*/
void analog_wr(int val_1, int val_2, int val_3) {
  analogWrite(p_1, val_1 - map(vision, 0, 100, 0, val_1));
  analogWrite(p_2, val_2 - map(vision, 0, 100, 0, val_2));
  analogWrite(p_3, val_3 - map(vision, 0, 100, 0, val_3));
}

void  lvlLight(byte a) {
  
  switch (a) {
    case 0:
      if (vision >= 100) vision = 0;
      else vision += 25;
      break;
    case 1:
      if (vision <= 0) vision = 100;
      else vision -= 25;
      break;

    case 2:
      if (vision<100){
       
        vision=100;
        } 
      else {
            
        vision = old_vision;
        
      }
      
      analogWrite(10,255);
      noInterrupts();
      delay(300);
      analogWrite(10,3);
     interrupts();
      break;

    case 3:
      if (vision >= 100) vision = 0;
      else vision += 10;
      break;
    case 4:
      if (vision <= 0) vision = 100;
      else vision -= 10;
      break;
  }
}

