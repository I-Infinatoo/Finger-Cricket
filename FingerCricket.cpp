/* ************************************************************************ */
/* ************************************************************************ */

#include<fstream.h>
#include<process.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<dos.h>

/* *******************  global func. and variables  *********************** */
/*                      ------ ----- --- ---------                          */

      void menu () ;                        //
      void timer () ;                       //
      void border () ;                      //    declaration of
      void time_display () ;                //    functions
      void over () ;                        //    globally
      void up_down () ;                     //

      void disp_file () ;                   // to disp. high scores
      void write_file () ;                  // used to save data in file


      int seconds = 0 ;                     // used in timer function
      int no_times = 0 ;                    // used for no. of plays

/* *******************       class : - player       *********************** */
/*                           -----     ------                               */

   class player
    {
	 char name [20] ;         // for player's
	 int clas ;               // information
	 int roll_no ;            //    ||

	 float balls ;                // used in
	 float score ;                // play function

	 double strike_rate ;          //  used in display function

      public :

	 void initial () ;        // to initialize the score

	 void play ( int entry ) ;                       // play function
	 void play_disp ( float score , float balls ) ;      // to display score

	 void input () ;          // to input player value

	 void calc_strike_rate ( float score , float balls ) ; // to calculate
							   // strike rate

	 void display () ;       // used in high score

	 int return_stk ()
	  {
	     return (strike_rate) ;
	  }    // accessor func. for strike rate

    } p , temp ;         // class

/* ********************    function to save data    *********************** */
/*                         ---------------------                            */
   void write_file ()
    {
      fstream file ( "F_C.dat" , ios :: app | ios :: binary ) ;

      fstream t_f ( "T_F.dat" , ios :: app | ios :: binary ) ;

	    if ( !file )
	     {
		 cout << " Data file is missing .... " ;

		 sleep ( 2 ) ;

		 menu () ;

	     }
      if ( no_times == 0 )
       {

	 file.write ( ( char* ) & p , sizeof ( p ) ) ;

       }

      else                                  // - (1)
      {
	while ( !file.eof () )
	 {
	   file.read ( ( char* ) & temp , sizeof ( temp ) ) ;

	   if ( p.return_stk() > temp.return_stk() )
	    {
	       t_f.write ( ( char* ) & p , sizeof ( p ) ) ;

	       t_f.write ( ( char* ) & temp , sizeof ( temp ) ) ;
	    }

	   //if ( temp.return_stk > strike_rate )
	   else
	    {
		t_f.write ( ( char* ) & temp , sizeof ( temp ) ) ;

		t_f.write ( ( char* ) & p , sizeof ( p ) ) ;

	    }

	 } // while

      }    // -(1)

      file.close () ;                   //   to close the files
      t_f.close () ;                    //        ||


      remove ( "F_C.dat" ) ;                  // replaceing the original
      rename ( "T_F.dat" , "F_C.dat" ) ;      // file with temp. file


    } // func.

/* ********************  function to initialize     *********************** */
/*                       ----------------------                             */

   void player :: initial ()
    {
	      balls = 0 ;
	      score = 0 ;
	      strike_rate = 0 ;

    }


/* *******************       use in high score      *********************** */
/*                           -----------------                              */

  void player :: display ()
   {
      clrscr () ;
      border () ;

      int x = 10 , y = 7 ;

       textcolor ( 11 ) ;  // light cyan

	gotoxy ( x , y ) ;
	cprintf ( " NAME           :   " ) ;     cout << name ;

	gotoxy ( x , y + 1 ) ;
	cprintf ( " CLASS          :   " ) ;     cout << clas ;

	gotoxy ( x , y + 2 ) ;
	cprintf ( " ROLL NUMBER    :   " ) ;     cout << roll_no ;

	gotoxy ( x , y + 4 ) ;
	cprintf ( " BALLS          :   " ) ;     cout << balls ;

	gotoxy ( x , y + 5 ) ;
	cprintf ( " SCORE          :   " ) ;     cout << score ;

	gotoxy ( x , y + 7 ) ;
	cprintf ( " STRIKE RATE    :   " ) ;     cout << strike_rate ;

      getch () ;

      menu () ;

    }

/*************************  used in high score  *****************************/
/*************************  ------------------  *****************************/

   void disp_file ()
    {
      fstream f ( "F_C.dat" , ios :: in | ios :: binary ) ;

      while ( !f.eof() )
       {
	 f.read ( (char*) & temp , sizeof (temp) ) ;

	 if ( f.eof () )
	  {
	    break ;
	  }

	 p.display () ;

	 getch () ;
	 clrscr () ;

       } // while

     clrscr () ;
     border () ;

     gotoxy ( 35 , 12 ) ;
     cout << " Thats all " ;

     getch () ;
     menu () ;

    } // func.

/* ********************  to input values from user  **********************  */
/*                       -------------------------                          */

   void player :: input ()
    {
	   _setcursortype ( _NOCURSOR ) ;

	  p.initial () ;  // to initiate the values before playing again

	  clrscr () ;
	  border () ;

	  textcolor ( 3 ) ;
	  gotoxy ( 29 , 6 ) ;
	  cprintf ( " ^^ FINGER CRICKET ^^ " ) ;


	  textcolor ( BROWN ) ;
	  gotoxy ( 6 , 8 ) ;
	  cprintf ( " >>  Enter Name      :  " ) ;          gets (name) ;


	     if ( strcmpi ( name , "exit" ) == 0 )   // if wants to exits
		   exit ( 0 ) ;

	  gotoxy ( 6 , 9 ) ;
	  cprintf ( " >>  Enter Class     :  " ) ;       cin >> clas ;
	  gotoxy ( 6 , 10 ) ;
	  cprintf ( " >>  Enter Roll no.  :  " ) ;    cin >> roll_no ;

	  delay ( 500 ) ;

	  clrscr () ;
	  border () ;

	  gotoxy ( 29 , 12 ) ;
	  textcolor ( 3 ) ;
	  cprintf ( " Get Ready For The Game " ) ;

	  delay ( 900 ) ;

	  clrscr () ;
	  border () ;

	  no_times++ ;    //............

	  timer () ;
    }


/* ******************** function to 'display score' **********************  */
/*                      --------------------------                          */

   void player :: play_disp ( float score ,float balls )
    {
	  _setcursortype ( _NOCURSOR ) ;

	gotoxy ( 20 ,11 ) ;                     //  will show
	textcolor ( YELLOW ) ;                  //  all over
	cprintf (" Total Score :  " ) ;         //  status of
	cout << score << endl ;                 //  balls played
	gotoxy ( 40 , 11 ) ;                    //  with score ( total )
	textcolor ( YELLOW ) ;
	cprintf ( " No. of balls played :  " ) ;
	cout << balls ;

	p.calc_strike_rate ( score , balls ) ;

    }


/* ********************  to calculate strike rate   *********************** */
/*                       ------------------------                           */

   void player :: calc_strike_rate ( float score ,float balls )
    {
	  _setcursortype ( _NOCURSOR ) ;

	strike_rate = ( score / balls ) * 100 ;

	gotoxy ( 30 , 12 ) ;                    // to calculate strike rate
	textcolor ( YELLOW ) ;
	cprintf ( " Strike Rate :  " ) ;
	cout << strike_rate ;

     } // func.

/* ********************            border           *********************   */
/*                                 ------                                   */

   void border ()             //for borders
    {
	  _setcursortype ( _NOCURSOR ) ;

	textcolor ( WHITE ) ;
	gotoxy ( 3 , 3 ) ;    //left

	 for ( int i = 3 ; i < 25 ; i++ )
	 {
	   cprintf ( "%c" , 58 ) ;
	   gotoxy ( 3 , i ) ;

	 }

	gotoxy ( 77 , 3 ) ;   //right

	 for ( i = 3 ; i < 25 ; i++ )
	 {
	   cprintf ( "%c" , 58 ) ;
	   gotoxy ( 77 , i ) ;

	 }

	gotoxy ( 4 , 3 ) ;    //up

	 for ( i = 4 ; i < 78 ; i++ )
	 {
	   cprintf ( "%c" , 45 ) ;
	   gotoxy ( i , 3 ) ;

	 }

	gotoxy ( 4 , 23 ) ;    //down

	 for ( i = 4 ; i < 78 ; i++ )
	 {
	   cprintf ( "%c" , 45 ) ;
	   gotoxy ( i , 23 ) ;

	 }

    }

/* *******************            load              **********************  */
/*                                ----                                      */

   void load ()                       //for loading screen
    {
	 _setcursortype ( _NOCURSOR ) ;

      int maze = 434 , block = 475 ;

	    gotoxy ( 33 , 9 ) ;
	    textcolor ( YELLOW ) ;

	    cprintf ( " LOADING ...." ) ;   // loading...

	    gotoxy ( 29 , 10 ) ;
	    textcolor ( WHITE ) ;

	for ( int i=0; i<19; i++)
	  {
	     cprintf ( "%c", maze ) ;           //temp
	  }

	    gotoxy ( 29 , 10 ) ;
	    textcolor ( GREEN ) ;

	for ( int j = 0 ; j < 19 ; j++ )
	  {
	     srand ( time (0) ) ;
					   //will generate diff. nos.
	     int time_load = rand() % 5 ;

	       if ( time_load == 0 )
		delay ( 0 ) ;

	       else if ( time_load == 1 )
		delay ( 250 ) ;

	       else if ( time_load == 2 )
		delay ( 200 ) ;

	       else if ( time_load == 3 )
		delay ( 100 ) ;

	       else if ( time_load == 4 )
		delay ( 70 ) ;

	       else
		delay ( 300 ) ;

		  cprintf ( "%c" , block ) ;       // print block  on maze

	  } //loop

    } // load

/* *******************           welcome            *********************** */
/*                               -------                                    */

   void welcome ()                // to welcome
    {

	  _setcursortype ( _NOCURSOR ) ;

      int vert = 435 , a = 303 , b = 348 ;

	    gotoxy ( 29 , 9 ) ;

	     textcolor ( 3 ) ;  //yellow
	     cprintf ("%c" , 257 ) ;      //face

	     textcolor ( 11 ) ;              // w
	     cprintf ( "  %c" , vert ) ; // vertical line
	     cprintf ( "%c" ,  a ) ;     // forward slash
	     cprintf ( "%c" ,  b ) ;     // backward slash
	     cprintf ( "%c" , vert ) ;

	     cprintf ( "ELCO" ) ;

	     cprintf ( "%c" , vert ) ;   //m
	     cprintf ( "%c" , b ) ;
	     cprintf ( "%c" , a ) ;
	     cprintf ( "%c" , vert ) ;

	     cprintf ( "E" ) ;

	     textcolor ( 3 ) ;
	     cprintf ( "  %c" , 257 ) ;   //face

    } //welcome

/* ********************             rule            *********************** */
/*                                  ----                                    */

   void rule ()                            //to print rules
    {
	   _setcursortype ( _NOCURSOR ) ;

	 border () ;
	 gotoxy ( 34 , 6 ) ;
	 textcolor ( RED ) ;

	 cprintf ( " RULES : " ) ;
	 gotoxy ( 35 , 7 ) ;

       for ( int i=0 ; i < 5 ; i++ )
	 cprintf ( "%c" , 205 ) ;     //underline

       textcolor ( YELLOW ) ;
       gotoxy ( 12 , 9 ) ;
       cprintf (" 1. Enter any number between 1 - 6 " ) ;
       gotoxy ( 12 , 10 ) ;
       cprintf (" 2. If your number is same as the number decided by the game " ) ;
       gotoxy ( 12 , 11 ) ;
       cprintf ( "              then your game will over !!! " ) ;
       gotoxy ( 12 , 12 ) ;
       cprintf ( " 3. If not, then your score for that ball will be the sum of the " ) ;
       gotoxy ( 12 , 13 ) ;
       cprintf ( "              numbers           " ) ;

       textcolor ( 128 + 6 ) ;
       gotoxy ( 15 , 15 ) ;
       cprintf ( "      ## ENTRY SHOULD BE DONE IN 6 SECONDS ## " ) ;

       gotoxy ( 41 , 20 ) ;

       textcolor ( 11 ) ;
       cprintf ( " Press any key to move back " ) ;
       getch () ;
       menu () ;                   // to go back to menu

    }

/* *******************           outline            *********************** */
/*                               -------                                    */

   void outline ()       // for showing out ( box )
    {
	    _setcursortype ( _NOCURSOR ) ;

	  textcolor ( RED ) ;
	  gotoxy ( 38 , 16 ) ;    //left

	     for ( int i=16 ; i <= 19 ; i++ )
	      {
		 cprintf ( "%c" , 179 ) ;
		 gotoxy ( 38 , i ) ;
	      }

	   gotoxy ( 44 , 16 ) ;   //right

	     for ( i=16 ; i <= 19 ; i++ )
	      {
		 cprintf ( "%c" , 179 ) ;
		 gotoxy ( 44 , i ) ;
	      }

	   gotoxy ( 38 , 16 ) ;    //up

	     for ( i=38 ; i <= 44 ; i++ )
	      {
		 cprintf ( "%c" , 196 ) ;
		 gotoxy ( i , 16 ) ;
	      }

	   gotoxy ( 38 , 19 ) ;    //down

	     for ( i=38 ; i <= 44 ; i++ )
	      {
		 cprintf ( "%c" ,196 ) ;
		 gotoxy ( i , 19 ) ;
	      }

    }

/* *******************             end              *********************** */
/*                                 ---                                      */

   void end ()
    {
	 _setcursortype ( _NOCURSOR ) ;

       border () ;

       textcolor ( GREEN ) ;
       gotoxy ( 30 , 10 ) ;
       cprintf ( " THANKYOU...." ) ;

       gotoxy ( 32 , 12 ) ;

       cprintf ( " !!! Hope You Enjoyed !!! " ) ;
       delay ( 900 ) ;

       textcolor ( 6 ) ;
       gotoxy ( 42 , 20 ) ;
       cprintf ( " Want to play again ? ( y / n ) " ) ;

       if ( getch() == 'y' )     //if want to play more
	{
	   clrscr () ;

	   p.input () ;

	}

       else                      // if want to do something else
	{
	   menu () ;
	}

    }

/* *******************            play              *********************** */
/*                                ----                                      */

   void player :: play ( int entry )      // function of class
    {
	 _setcursortype ( _NOCURSOR ) ;

	clrscr () ;
	border () ;

      int no_comp ;

      textcolor ( 3 ) ;
      gotoxy ( 29 , 6 ) ;
      cprintf ( " ^^ FINGER CRICKET ^^ " ) ;


       if ( entry == 49 )           // if entry = 1
	    entry = 1 ;

       if ( entry == 50 )           // if entry = 2
	    entry = 2 ;

       if ( entry == 51 )           // if entry = 3
	    entry = 3 ;

       if ( entry == 52 )           // if entry = 4
	    entry = 4 ;

       if ( entry == 53 )           // if entry = 5
	    entry = 5 ;

       if ( entry == 54 )           // if entry = 6
	    entry = 6 ;


		  while ( entry >= 1 && entry <= 6 )

		  {    textcolor ( YELLOW ) ;
		       gotoxy ( 20 , 6 ) ;
		       srand ( time(0) ) ;

		      int no_comp = 1+rand() % 6 ;    //comp.'s no
		      int temp_score = 0 ;

			gotoxy ( 20 , 7 ) ;
			textcolor ( YELLOW ) ;
			cprintf ( " Your no. : " ) ;
			gotoxy ( 33 , 8 ) ;
			cprintf ( "---" ) ;         // underlining no.
			textcolor ( YELLOW ) ;

			gotoxy ( 34,7 ) ;
			cout << entry ;

			gotoxy ( 45 , 7 ) ;
			textcolor ( YELLOW ) ;
			cprintf ( " comp.'s no. :  " ) ;
			cout << no_comp ;

			if ( entry != no_comp )
			   {
			       temp_score = entry + no_comp ;

			       gotoxy ( 20 , 11 ) ;
			       textcolor ( YELLOW ) ;
			       cprintf ( " Score :  " ) ;
			       cout << temp_score ;

			       ++balls ;           //count no. of balls
			       score += temp_score ;

			       delay ( 900 ) ;
			       gotoxy ( 5 , 17 ) ;
			       cprintf ( " Next Ball... " ) ;

			       delay ( 900 ) ;
			       clrscr () ;
			       timer () ;
			   }

		     else if( entry == no_comp )       // if no. matched
			   {

			       sound ( 100 ) ;      // sound if
			       delay ( 500 ) ;      //    out
			       nosound () ;

			       outline () ;
			       gotoxy ( 40,18 ) ;
			       textcolor ( 4+128 ) ;
			       cprintf ("OUT") ;
			       ++balls ;
			       break ;
			   }

		  } //while


      if( entry >= 65 && entry <= 122 )            //  if any
       {                                           //  character entered
						   //  then, terminate
						   //  the programe
	  ++balls ;    // to count the no. of balls

	  sound ( 100 ) ;      // sound if
	  delay ( 500 ) ;      //    out
	  nosound () ;

	  gotoxy ( 32 , 15 ) ;
	  cprintf ( " Charcter Entered " ) ;
	  delay ( 1000 ) ;

	  p.play_disp ( score , balls ) ;   // to disply the scores

	  write_file () ;        // to store data

	  delay ( 1000 ) ;

	  gotoxy ( 29 , 16 ) ;
	  cprintf ( " Exiting from the game " ) ;

	  delay ( 1000 ) ;
	  exit ( 0 ) ;
       }

     else if ( entry > 54 || entry == 48 )       // if no. entered is > 6
       {                                         // or equal to 0
	  ++balls ;   // to count the no. of balls

	  sound ( 100 ) ;      // sound if
	  delay ( 500 ) ;      //    out
	  nosound () ;

	  gotoxy ( 36,8 ) ;
	  textcolor ( YELLOW ) ;
	  cprintf (" Invalid no ") ;
	  delay ( 900 ) ;

	  p.play_disp ( score , balls ) ;  // to display the scores

	  write_file () ;        // to store data

	  sleep ( 3 ) ;     // similar as delay for 3000 milliseconds

	  menu () ;

       }

     p.play_disp ( score , balls ) ;  // to display the scores

     write_file () ;        // to store data

     sleep ( 3 ) ;          // similar as delay for 3000 milliseconds

     getch () ;
     clrscr () ;
     border () ;

     menu () ;

    }  // function

/* *******************           made by            *********************** */
/*                               -------                                    */

   void designed_by ()
    {
	 _setcursortype ( _NOCURSOR ) ;

       clrscr () ;
       border () ;

       gotoxy ( 29 , 12 ) ;
       textcolor ( 3 ) ;
       cprintf ( " Designed By : ISHU RAJAN " ) ;
       gotoxy ( 40 , 13 ) ;
       cprintf ( "  XII 'A' " ) ;

       gotoxy ( 41 , 20 ) ;
       cprintf ( " Press any key to move back " ) ;
       getch () ;
       menu () ;        // to move back to menu

    }

/* *******************             menu             *********************** */
/*                                 ----                                     */

   void menu ()
    {

      int x = 32 ;
      int y = 12 ;

      int x1 = 0 , y1 = 0 ;

      clrscr () ;
      border () ;

      textcolor ( 3 ) ;
      gotoxy ( x-3 , 6 ) ;
      cprintf ( " ^^ FINGER CRICKET ^^ " ) ;

      up_down () ;

	_setcursortype ( _SOLIDCURSOR ) ;

      textcolor ( 6 ) ;
      gotoxy ( x+4 , 10 ) ;
      cprintf ( " MENU " ) ;
      gotoxy ( x , y+1 ) ;
      cprintf ( " >>   PLAY THE GAME " ) ;
      gotoxy ( x , y+2 ) ;
      cprintf ( " >>   HIGH SCORE " ) ;
      gotoxy ( x , y+3 ) ;
      cprintf ( " >>   RULES " ) ;
      gotoxy ( x , y+4 ) ;
      cprintf ( " >>   DESIGNED BY " ) ;
      gotoxy ( x , y+5 ) ;
      cprintf ( " >>   EXIT " ) ;

      gotoxy ( x + 4 , y + 1 ) ;

      x1 = x ;
      y1 = y + 1 ;

     while (1)
      {
	 char ch ;
	 ch = getch ();

	switch (ch)
	 {
	   case 's':
	   case 80 :  y1++ ;                   // down
		      if( y1 > y + 5 )
		       {
			  y1 = y + 1 ;
		       }
		      gotoxy ( x1 + 4 , y1 ) ;

		      break ;

	   case 'w':
	   case 72 :  y1-- ;                   // up
		      if( y1 < y + 1 )
		       {
			  y1 = y + 5 ;
		       }
		      gotoxy ( x1 + 4 , y1 ) ;

		      break ;

	   case 13 :   if( y1 == y + 1 )
			{
			  clrscr () ;
			  p.input () ;

			  break ;
			}

		       else if ( y1 == y + 2 )
			{
			  clrscr () ;
			  //p.display () ;
			  disp_file () ;   //............
			  break ;
			}

		       else if ( y1 == y + 3 )
			{
			  clrscr () ;
			  rule () ;

			  break ;
			}

		       else if ( y1 == y + 4 )
			{
			  designed_by () ;

			  break ;
			}

		       else if ( y1 == y + 5 )
			{
			  exit ( 0 ) ;
			}


		      break ;    //  case's

	 } //shitch

      }  // while

    }  //menu

/* ********************           timer             *********************** */
/*                                -----                                     */

   void timer ()
    {
       _setcursortype ( _NOCURSOR ) ;

	int entry = 0 ;
	seconds = 6 ;

	  while ( seconds >= 0 )
	   {
	      time_display () ;
	      delay ( 900 ) ;

		if ( kbhit () )
		 {
		   entry = getch () ;
		   p.play ( entry ) ;
		 }

		if ( seconds == 0 )      // sound if time over
		 {
		   sound ( 100 ) ;
		   delay ( 500 ) ;
		   nosound () ;
		 }

		 if ( seconds > 0 )      // sonud while time
		 {                       // is not over
		   sound ( 400 ) ;
		   delay ( 100 ) ;
		   nosound () ;
		 }

	       seconds-- ;

	   }  //while

	 over () ;

    }

/* ********************       time_display          *********************** */
/*                            ------------                                  */

   void time_display ()
    {
	_setcursortype ( _NOCURSOR ) ;

       border () ;
       gotoxy ( 5 , 15 ) ;
       cout << " Seconds remaining :  " << seconds ;

      textcolor ( 3 ) ;
      gotoxy ( 29 , 6 ) ;
      cprintf ( " ^^ FINGER CRICKET ^^ " ) ;

       gotoxy ( 20 , 7 ) ;
       textcolor ( YELLOW ) ;
       cprintf ( " Your no. : " ) ;
       gotoxy ( 33 , 8 ) ;
       cprintf ( "---" ) ;         // underlining no.
       textcolor ( YELLOW ) ;

       gotoxy ( 34 , 7 ) ;  // where no. will enter


    }

/* ********************            over             *********************** */
/*                                 ----                                     */

   void over ()
    {
	_setcursortype ( _NOCURSOR ) ;

       clrscr () ;
       border () ;

       gotoxy ( 35 , 6 ) ;
       cout << " TIME OUT " ;
       delay ( 900 ) ;

       end () ;

    }

/* ********************           up_down           *********************** */
/*                                -------                                   */

   void up_down ()
    {
	 textcolor ( 3 ) ;
	 gotoxy ( 60 , 8 ) ;
	 cprintf ( " w :-  up " ) ;
	 gotoxy ( 60 , 9 ) ;
	 cprintf ( " s :- down " ) ;
	 gotoxy ( 63 , 10 ) ;
	 cprintf ( " or " ) ;
	 gotoxy ( 59 , 11 ) ;
	 cprintf ( " arrow keys " ) ;

    }

/* ********************          main               *********************** */
/*                               ----                                       */

   void main ()
    {

	  clrscr () ;

	  border () ;
	  load () ;

	  delay ( 400 ) ;
	  welcome () ;

	  delay ( 900 ) ;
	  clrscr () ;
	  border () ;

	  menu () ;

      getch () ;


    }


/* ************************************************************************ */
/* ************************************************************************ */