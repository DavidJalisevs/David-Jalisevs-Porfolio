*-------------------------------------------------------
* STARTING MEMORY ADDRESS FOR THE PROGRAMME $1000
*-------------------------------------------------------
    
    ORG $1000

*-------------------------------------------------------
*CHOOSE TO BE A PLUMBER OR A RABBIT 
*-------------------------------------------------------

*-------------------------------------------------------
*VALIDATION VALUES TO BE USED, MODIFY AS NEEDED
*ADD ADDITIONAL VALIDATION VALUES AS REQUIRED
*-------------------------------------------------------
EXIT        EQU 0      USED TO EXIT ASSEMBLY PROGRAM
MIN_POTIONS EQU 1      MIN NUMBER OF POTIONS
MAX_POTIONS EQU 9      MAX NUMBER OF POTIONS
MIN_WEAPONS EQU 1      MIN WEAPONS
MAX_WEAPONS EQU 3      MAX WEAPONS
WIN_POINT   EQU 5      POINTS ACCUMILATED ON WIN
LOSE_POINT  EQU 8      POINTS DEDUCTED ON A LOSS
PLAYER_HP   EQU 13     PLAYER HEALTH POINTS
ENEMY_HP    EQU 13      ENEMY HEALTH 
MINE_LOC    EQU 100    USED BELOW FOR SOME SIMPLE COLLISION DETECTION USING CMP
FAST_DMG    EQU 2      HOW MUCH FAST ATTACK HITS
STRONG_DMG  EQU 5    HOW MUCH STRONG ATTACK HITS 
HEAL_NUM    EQU 5             
ENEMY_DMG   EQU 3      ENEMY DAMAGE 

*START OF GAME
START:
    MOVE.B  #100,$4000 PUT SCORE/HEALTH IN MEMORY LOCATION $4000
    LEA     $4000,A3   ASSIGN ADDRESS A3 TO THAT MEMORY LOCATION
    
    MOVE.B  #PLAYER_HP,$3010
    LEA     $3010,A4
    
    MOVE.B  #ENEMY_HP,$3020
    LEA     $3020,A5
    
    
    
    BSR     WELCOME    BRANCH TO THE WELCOME SUBROUTINE

   *BSR     INPUT      BRANCH TO THE INPUT SUBROUTINE
    BSR     GAME       BRANCH TO THE GAME SUBROUTINE
*GAME LOOP
    ORG     $3000      THE REST OF THE PROGRAM IS TO BE LOCATED FROM 3000 ONWARDS

*-------------------------------------------------------
*-------------------GAME SUBROUTINE---------------------
*-------------------------------------------------------
GAME:

    BSR     GAMELOOP   BRANCH TO GAMELOOP SUBROUTINE
    RTS                RETURN FROM GAME: SUBROUTINE
          
END:
    SIMHALT

*-------------------------------------------------------
*-------------------WELCOME SUBROUTINE------------------
*-------------------------------------------------------
WELCOME:
    BSR     ENDL            BRANCH TO ENDL SUBROUTINE
    LEA     WELCOME_MSG,A1  ASSIGN MESSAGE TO ADDRESS REGISTER A1
    MOVE.B  #14,D0          MOVE LITERAL 14 TO DO
    TRAP    #15             TRAP AND INTERPRET VALUE IN D0
    BSR     ENDL            BRANCH TO ENDL SUBROUTINE
    RTS                     RETURN FROM WELCOME: SUBROUTINE

*-------------------------------------------------------
*---------GAMEPLAY INPUT VALUES SUBROUTINE--------------
*-------------------------------------------------------    
INPUT:
    BSR     POTIONS         BRANCH TO POTION INPUT SUBROUTINE
    BSR     WEAPONS         BRANCH TO WEAPONSS INPUT SUBROUTINE
    RTS

*-------------------------------------------------------
*----------------GAMELOOP (MAIN LOOP)-------------------
*------------------------------------------------------- 
GAMELOOP:
   * BSR     UPDATE          BRANCH TO UPDATE GAME SUBROUTINE 
   * BSR     CLEAR_SCREEN    CLEARS THE SCREEN         
   * BSR     DRAW            BRANCH TO DRAW SCREEN SUBROUTINE
    BSR     CLEAR_SCREEN    CLEARS THE SCREEN
    BSR     GAMEPLAY        BRANCH TO GAMEPLAY SUBROUTINE

    *BSR     CLEAR_SCREEN    CLEARS THE SCREEN
    *BSR     HUD             BRANCH TO DISPLAY HUD SUBROUTINE
    *BSR     CLEAR_SCREEN    CLEARS THE SCREEN
    *BSR     REPLAY          BRANCH TO REPLAY GAME SUBROUTINE
    *BSR     CLEAR_SCREEN    CLEARS THE SCREEN
    RTS                     RETURN FROM GAMELOOP: SUBROUTINE

*-------------------------------------------------------
*----------------UPDATE QUEST PROGRESS------------------
*  COMPLETE QUEST
*------------------------------------------------------- 
UPDATE:
    BSR     ENDL            PRINT A CR AND LF
    BSR     DECORATE        DECORATE WITH DOTS USING A LOOP
    LEA     UPDATE_MSG,A1   
    MOVE.B  #14,D0
    TRAP    #15
    BSR     DECORATE
    RTS
*-------------------------------------------------------
*-----------------DRAW QUEST UPDATES--------------------
* DRAW THE GAME PROGRESS INFORMATION, STATUS REGARDING
* QUEST
*------------------------------------------------------- 
DRAW:
    BSR     ENDL
    BSR     DECORATE
    LEA     DRAW_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    BSR     DECORATE
    RTS

*-------------------------------------------------------
*--------------------POTIONS INVENTORY---------------------
* NUMBER OF POTIONS TO BE USED IN A QUEST 
*------------------------------------------------------- 
POTIONS:
    BSR     ENDL
    BSR     DECORATE
    LEA     POTIONS_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    BSR     DECORATE
    RTS

*-------------------------------------------------------
*-------------------------WEAPONS-----------------------
* NUMBER OF WEAPONS
*-------------------------------------------------------   
WEAPONS:
    BSR     ENDL
    BSR     DECORATE
    LEA     WEAPONS_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    BSR     DECORATE
    RTS

*-------------------------------------------------------
*---GAME PLAY (QUEST PROGRESS)--------------------------
*------------------------------------------------------- 
GAMEPLAY:
    BSR     ENDL
    *BSR     DECORATE
    BSR     FIRSTFIGHT      BRANCH TO FIRSTFIGHT SUBROUTINE
    

  *  LEA     GAMEPLAY_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    MOVE.B  #4,D0
    TRAP    #15
   * BSR     DECORATE
   * BSR     COLLISION
    RTS

*-------------------------------------------------------
*-----------------HEADS UP DISPLAY (SCORE)--------------
* RETRIEVES THE SCORE FROM MEMORY LOCATION
*-------------------------------------------------------   
HUD:

    BSR     ENDL
    BSR     DECORATE
    LEA     HUD_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    MOVE.B  (A3),D1     RETRIEVE THE VALUE A3 POINT TO AND MOVE TO D1
    MOVE.B  #3,D0       MOVE LITERAL 3 TO D0
    TRAP    #15         INTREPRET VALUE IN D0, WHICH 3 WHICH DISPLAYS D1
    BSR     DECORATE
    RTS

*-------------------------------------------------------
*-----------------------BEING ATTACKED------------------
* THIS COULD BE USED FOR COLLISION DETECTION
*-------------------------------------------------------
COLLISION:
    MOVE.B  #MINE_LOC,D1
    CMP     #100,D1 IS( X == 100)?
	BNE     COLLISION_MISS IF X IS EQUAL TO 100, THEN HIT
FASTATTACK_HIT:
    *HIT 
    BSR     ENDL
    LEA     HIT_MSG,A1
    MOVE    #14,D0
    TRAP    #15
    
    *sub from HP  
    MOVE.B  $3020,D0
    MOVE.B  #FAST_DMG,D3
    SUB.B   D3,D0

    MOVE.B  D0,$3020
    LEA     $3020,A5
    MOVE.B  $3020,D1

    LEA     ENEMYHP_MSG,A1
    MOVE    #14,D0
    TRAP    #15

    MOVE #3,D0
    TRAP #15
    BSR     ENDL    
   
    RTS
    
STRONGATTACK_HIT:
    *strong ATTACK
    BSR     ENDL
    LEA     HIT_MSG,A1
    MOVE    #14,D0
    TRAP    #15
    
    *ATTACK  
    MOVE.B  $3020,D0
    MOVE.B  #STRONG_DMG,D3
    SUB.B   D3,D0

    MOVE.B  D0,$3020
    LEA     $3020,A5
    MOVE.B  $3020,D1

    LEA     ENEMYHP_MSG,A1
    MOVE    #14,D0
    TRAP    #15

    MOVE    #3,D0
    TRAP    #15
    BSR     ENDL    
   
    RTS    
    
    
RABBIT_HITS:
  *HIT 
    BSR     endl
    *sub from HP 
    MOVE.B  $3010,D0
    MOVE.B  #ENEMY_DMG,D3
    SUB.B   D3,D0

    MOVE.B  D0,$3010
    LEA     $3010,A5
    MOVE.B  $3010,D1

    LEA     PLAYERHP_MSG,A1
    MOVE    #14,D0
    TRAP    #15

    MOVE #3,D0
    TRAP #15
    BSR     ENDL    
    
    
   
    RTS
    
PLAYER_HEAL:
    *strong ATTACK
    *bsr     endl
    *lea     HEALED_MSG,A1
    *move    #14,D0
    *trap    #15
  *HIT 
    BSR     endl
    *sub from HP 
    MOVE.B  $3010,D0
    ADD.B   #HEAL_NUM,D0

    MOVE.B  D0,$3010
    LEA     $3010,A5
    MOVE.B  $3010,D1

   * lea     PLAYERHP_MSG,A1
   * move    #14,D0
   * trap    #15
*
   * MOVE #3,D0
   * TRAP #15
    BSR     ENDL    
   
    RTS


COLLISION_MISS:
    *MISS
    LEA     MISS_MSG,A1
    MOVE    #14,D0
    TRAP    #15
    RTS

*-------------------------------------------------------
*--------------------------LOOP-------------------------
*-------------------------------------------------------
LOOP:
    MOVE.B  #5, D3 LOOP COUNTER D3=5
NEXT:
    LEA     LOOP_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
	SUB     #1,D3   DECREMENT LOOP COUNTER
    BNE     NEXT    REPEAT UNTIL D0=0

*-------------------------------------------------------
*------------------SCREEN DECORATION--------------------
*-------------------------------------------------------
DECORATE:
    MOVE.B  #60, D3
    BSR     ENDL
OUT:
    LEA     LOOP_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
	SUB     #1,D3   DECREMENT LOOP COUNTER
    BNE     OUT	    REPEAT UNTIL D0=0
    BSR     ENDL
    RTS
    
CLEAR_SCREEN: 
    MOVE.B  #11,D0      CLEAR SCREEN
    MOVE.W  #$FF00,D1
    TRAP    #15
    RTS
*-------------------------------------------------------
*------------------------REPLAY-------------------------
*-------------------------------------------------------
REPLAY:
    BSR     ENDL
    LEA     REPLAY_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    
    MOVE.B  #10,PLAYER_HP
    MOVE.B  #10,ENEMY_HP

    
    
    
    
    MOVE.B  #4,D0
    TRAP    #15

    CMP     #EXIT,D1
    BEQ     END         IF SR Z REGISTER CONTAINS 1 BEQ => BRANCH EQUALS
    BSR     GAMELOOP

ENDL:
    MOVEM.L D0/A1,-(A7)
    MOVE    #14,D0
    LEA     CRLF,A1
    TRAP    #15
    MOVEM.L (A7)+,D0/A1
    RTS
    
*-------------------------------------------------------
*------------------------FIRSTFIGHT---------------------
*-------------------------------------------------------
FIRSTFIGHT:

    LEA     WEAPON_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
  * TAKE INPUT FROM PLAYER 
    MOVE.B  #4,D0
    TRAP    #15

    BSR     SWORDWEAPON    BRANCH TO FIRSTFIGHT SUBROUTINE
    
    *BSR     CLEAR_SCREEN    CLEARS THE SCREEN
    LEA     RABATTACK_MSG,A1  RABBIT ATTACK MESSAGE
    MOVE.B  #14,D0
    TRAP    #15
    BSR     PLAYERMOVE    
    
    
*-------------------------------------------------------
*------------------------SWORDWEAPON------------------------
*-------------------------------------------------------
SWORDWEAPON:

    LEA     SWORDWEAPON_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    RTS

*-------------------------------------------------------
*------------------------PLAYERMOVE---------------------
*-------------------------------------------------------
PLAYERMOVE:
    LEA     MOVECHOICE_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15

    LEA     FIRSTMOVE_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    LEA     SECONDMOVE_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    LEA     THIRDMOVE_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    
    

*if statement to check what user is willing to do 
    MOVE.B  #4,D0
    TRAP    #15
    CMP     #2,D1
    BEQ     MASSIVEATTACK
    CMP     #1,D1
    BEQ     FASTATTACK
    CMP     #3,D1
    BEQ     HEAL
    LEA     THIRDMOVE_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15

    

    

*-------------------------------------------------------
*------------------------FASTATTACK---------------------
*-------------------------------------------------------
FASTATTACK:

    LEA     FASTATTACK_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    BSR     FASTATTACK_HIT
   
    MOVE.B $3020,D0
    
    CMP     #0,D0
    BEQ     GAMEWON
    
    
    CMP     #240,D0
    BGT     GAMEWON
    
    
    BNE     RABBITATTACK
    RTS
*-------------------------------------------------------
*------------------------MASSIVEATTACK------------------
*-------------------------------------------------------
MASSIVEATTACK:

    LEA     MASSIVEATTACK_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    BSR     STRONGATTACK_HIT
    
    MOVE.B $3020,D0
    
    CMP     #0,D0
    BEQ     GAMEWON
    
    CMP     #240,D0
    BGT     GAMEWON
    
    
    BNE     RABBITATTACK    
    RTS
*-------------------------------------------------------
*------------------------HEAL------------------------
*-------------------------------------------------------
HEAL:

    LEA     DEFENSE_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    BSR     PLAYER_HEAL       WILL CALL LATER FOR  HEAL
    BSR     RABBITATTACK

    RTS
    
    
*-------------------------------------------------------
*------------------------RABBITATTACK---------------------
*-------------------------------------------------------
RABBITATTACK:

    LEA     RABBITATTACK_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    BSR     RABBIT_HITS
    
    MOVE.B $3010,D4
    
    CMP     #0,D4
    BEQ     GAMELOST
    
    
    CMP     #240,D4
    BGT     GAMELOST


    
    BSR     FIRSTFIGHT
    

*-------------------------------------------------------
*------------------------GAMEWON---------------------
*-------------------------------------------------------
GAMEWON:

    BSR     CLEAR_SCREEN
    LEA     GAMEWON_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    BSR     REPLAY
    
    
*-------------------------------------------------------
*------------------------GAMELOST---------------------
*-------------------------------------------------------
GAMELOST:

    BSR     CLEAR_SCREEN
    LEA     GAMELOST_MSG,A1
    MOVE.B  #14,D0
    TRAP    #15
    BSR     REPLAY
    
        
    
*-------------------------------------------------------
*-------------------DATA DELARATIONS--------------------
*-------------------------------------------------------

CRLF:           DC.B    $0D,$0A,0
WELCOME_MSG:    DC.B    '************************************************************'
                DC.B    $0D,$0A
                DC.B    'RABBITS VS PLUMBERS GAME'
                DC.B    $0D,$0A
                DC.B    '************************************************************'
                DC.B    $0D,$0A,0
POTION_MSG:     DC.B    'POTION ....'
                DC.B    $0D,$0A
                DC.B    'ENTER POTION : ',0
POTIONS_MSG:    DC.B    'NUMBER OF POTIONS : ',0
WEAPONS_MSG:    DC.B    'EACH QUEST NEED AT LEAST 2 WEAPONS'
                DC.B    $0D,$0A
                DC.B    'MINIMUM REQUIREMENT IS 2 I.E. SWORD X 1 AND SPEER X 1.'
                DC.B    $0D,$0A
                DC.B    'ENTER # OF WEAPONS : ',0
GAMEPLAY_MSG:   DC.B    'ADD GAMEPLAY !',0
UPDATE_MSG:     DC.B    'UPDATE GAMEPLAY !',0
DRAW_MSG:       DC.B    'DRAW SCREEN !',0
WEAPON_MSG:     DC.B    'THIS IS YOUR FIGHT ---- DEFEND THE CASTLE !!',0
RABATTACK_MSG   DC.B    'RABBIT ATTACKS YOU!'
                DC.B    $0D,$0A,0
MOVECHOICE_MSG  DC.B    'CHOOSE YOUR MOVE!'
                DC.B    $0D,$0A,0
MISS_MSG:       DC.B    'MISS!',0
SWORDWEAPON_MSG DC.B    'YOU GOT A SWORD !!!'
                DC.B    $0D,$0A,0
FIRSTMOVE_MSG   DC.B    ' 1 - FAST ATTACK!'
                DC.B    $0D,$0A,0
SECONDMOVE_MSG  DC.B    ' 2 - MASSIVE ATTACK!'
                DC.B    $0D,$0A,0
THIRDMOVE_MSG   DC.B    ' 3 - DEFENSE!'
                DC.B    $0D,$0A,0
FASTATTACK_MSG  DC.B    'YOU HAVE USED FAST ATTACK!'
                DC.B    $0D,$0A,0  
MASSIVEATTACK_MSG  DC.B    'YOU HAVE USED MASSIVE ATTACK!'
                DC.B    $0D,$0A,0       
DEFENSE_MSG     DC.B    'YOU HAVE USED HEAL!'
                DC.B    $0D,$0A,0         
ENEMYHP_MSG     DC.B    'ENEMY HAS LEFT WITH HEALTH OF : ',0 
PLAYERHP_MSG    DC.B    'PLYAER HAS LEFT WITH HEALTH OF : ',0 
HIT_MSG         DC.B    'ATTACK !!!!!!!!!'
                DC.B    $0D,$0A,0    
HEALED_MSG      DC.B    'PLAYER HEALED HIMSELF !!!!!!!!!'
                DC.B    $0D,$0A,0  
RABBITATTACK_MSG DC.B    'RABBIT ATTACKS YOU !!!!!!!!!'
                DC.B    $0D,$0A,0             
GAMEWON_MSG     DC.B    'YOU WON !!!!!!!!!',$0D,$0A,0 
GAMELOST_MSG    DC.B    'YOU LOST !!!!!!!!!',$0D,$0A,0                        


LOOP_MSG:       DC.B    '.',0
REPLAY_MSG:     DC.B    'ENTER 0 TO QUIT ANY OTHER NUMBER TO REPLAY : ',0
HUD_MSG:        DC.B    'SCORE : ',0

HEALTH:     DS.W    1   PLAYERS HEALTH
SCORE:      DS.W    1   RESERVE SPACE FOR SCORE

    END START



*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
