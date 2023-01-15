#include <SDL2/SDL.h>
#include <stdlib.h>
#include <gtk/gtk.h>
//#include "audio.h"
#include <SDL2/SDL_mixer.h>
#include <fmod.h>
#include "fmod.hpp"
#include "common.h"
//#include <pulse/simple.h>
#include <gdk/gdkkeysyms.h>
//TODO: 
//make h_scale follow song:DONE
//check hscale_moved function:DONE
//Get fmod working:DONE!
//get song length:DONE
//make hadjustment follow song length channel set position:DONE
//maybe try converting app to cplus?:DONE
//slider increments but crashes:FIXED


 GtkWidget *treeView;
 GtkWidget *window; 
GtkWindow *Window;
 GtkTreeSelection *selection;
  GtkTreeModel     *model;
  GtkTreeIter       iter;
 GtkTreeViewColumn *column;
 GtkTreePath       *path;
 GtkListStore *store; 
 GtkTreeView *treeview;
 GtkAdjustment *hadjustment;
// GtkWidget *h_scale;


char *str;
char *filename;
char *f1;
 char tracks[6];
//char *filename;
int *rowElements[6];
gint a;
int trackPos = 0;
unsigned int lastTime = 0, currentTime;
//FMOD_SYSTEM *System;
//FMOD_RESULT result;
//FMOD_SOUND *sound;
//FMOD_CHANNEL *channel = 0;
//FMOD_CHANNELGROUP *channelgroup;
bool paused = 0;
//FMOD_RESULT result;
//FMOD_CHANNEL    *channel = 0;
//int position;
unsigned int version;
//void *extradriverdata = 0;
int numsubsounds;
//int position;
//test
int length;
//unsigned int *ms = 0;
gdouble pos;
// FMOD::Channel    *channel = 0;
 FMOD::Channel    *channel = 0;
   FMOD_RESULT       result;  
unsigned int ms = 1000;
unsigned int lenms = 0;
int value = 1000;
enum {

  LIST_ITEM = 0,
  N_COLUMNS
};
//test
gboolean timeout_func(gpointer data) {
//    printf("teta = %d\n", ++teta);
result = channel->getPosition(&ms,FMOD_TIMEUNIT_MS);
gtk_adjustment_get_value(hadjustment);
value += 1000;
gtk_adjustment_set_value(hadjustment,ms);//value
// value + 1000;
printf("value:%d",value);
   return TRUE;
}
bool change;

int FMOD_Main(gchar *song){//gchar *song
//FMOD_SYSTEM     *system;
  //  FMOD_SOUND      *sound, *sound_to_play;
   // FMOD_CHANNEL    *channel = 0;
   // FMOD_RESULT       result;
  // FMOD_CHANNELGROUP *channelgroup;


FMOD::System     *system;
    FMOD::Sound      *sound, *sound_to_play;
//    FMOD::Channel    *channel = 0;
  //  FMOD_RESULT       result;  
  unsigned int      version;
    void             *extradriverdata = 0;
    int               numsubsounds;
  Common_Init(&extradriverdata);

result = FMOD::System_Create(&system);
 result = system->init(32,FMOD_INIT_NORMAL,extradriverdata); 
ERRCHECK(result);

result = system->createStream(song,FMOD_DEFAULT,0,&sound);//FMOD_LOOP_NORMAL | FMOD_2D
//int length;
//unsigned int position = 0;
//int ms;
float *frequency;
//result = system->playSound(sound,0,false,&channel);


result = system->playSound(sound,0,false,&channel);

FMOD_TIMEUNIT lengthtype;
//int length;
//int position;
char *name;
//unsigned int ms;
//get song position
//result = FMOD_Channel_GetPosition(&channel,&ms,FMOD_TIMEUNIT_MS);
result = sound->getLength(&lenms,FMOD_TIMEUNIT_MS);
if(result != FMOD_OK){
printf("not playing");
}

gtk_adjustment_get_upper(hadjustment);
gtk_adjustment_set_upper(hadjustment,lenms);

g_timeout_add(1500, timeout_func, NULL);//1000


}

//test
void delete_char(char *str, int i) {
    int len = strlen(str);

    for (; i < len - 1 ; i++)
    {
       str[i] = str[i+1];
    }

    str[i] = '\0';
}
void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

//test
void
  view_onRowActivated (GtkTreeView        *treeview,
                       GtkTreePath        *path,
                       GtkTreeViewColumn  *col,
//                      GtkTreeIter *iter,
                       gpointer            userdata)
  {
  gint int_data;
 gchar *str_data;

  // GtkTreeIter iter;
  // GtkTreeModel *model = gtk_tree_view_get_model(treeview);

   if (gtk_tree_model_get_iter(GTK_TREE_MODEL(store), &iter, path)) {
     // gtk_tree_model_get (GTK_LIST_STORE(store), &iter, LIST_ITEM, &int_data, 1, &str_data, -1);
//     gtk_tree_model_get (GTK_LIST_STORE(store), &iter, LIST_ITEM, &str_data, -1);
   gtk_tree_model_get (GTK_TREE_MODEL(store), &iter, LIST_ITEM, &str_data, -1);
  
     
    // Here the variables int_data and str_data should be filled with

      // relevant data
     g_print("path:%s",str_data);
 //playMusic(str_data,SDL_MIX_MAXVOLUME / 2);
//program succeeds with creating stream but fails when playing sound
result = channel->stop();
FMOD_Main(str_data);
//FMOD_Main();
   }



  }


void hscale_moved (GtkRange *range,
              gpointer  user_data)
{
//   GtkWidget *label = user_data;
  // GtkWidget *label;
  // gdouble pos = gtk_range_get_value (range);
  pos = gtk_range_get_value (range); 
 
 result = channel->getPosition(&ms,FMOD_TIMEUNIT_MS);
  result = channel->setPosition(pos,FMOD_TIMEUNIT_MS);//10000
  

 gchar *str = g_strdup_printf ("Horizontal scale is %d", ms);//%.0fpos
//   gtk_label_set_text (GTK_LABEL (label), str);//ste

//FMOD_Main("hi.mp3");
   g_free(str);
}
//test
void init_list(GtkWidget *list) {

  GtkCellRenderer *renderer;
 // GtkTreeViewColumn *column;
  GtkListStore *store;


  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes("Now Playing:",
          renderer, "text", LIST_ITEM, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list), 
      GTK_TREE_MODEL(store));
//test
 
//test
  g_object_unref(store);
}

void add_to_list(GtkWidget *list, char *str) {//char *str
    
 
  store = GTK_LIST_STORE(gtk_tree_view_get_model (GTK_TREE_VIEW(list)));
//  delete_char(str,5);

  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
  gtk_tree_model_get(GTK_TREE_MODEL(store),&iter,LIST_ITEM,&str,-1);
   a = gtk_tree_model_iter_n_children (GTK_TREE_MODEL(store),NULL) ;//NULL
 
//gint a =

int ran = rand() % a;
//  }



  char *track[50];
  int i;
  for(ran=0;ran<50;ran++){//1
  track[ran];
  track[ran] = str;
//  playMusic(track[ran], SDL_MIX_MAXVOLUME / 2);//1
  }


}
//test

//test

void openKey()
{
GtkWidget *dialog;
GSList *filenames;

     dialog = gtk_file_chooser_dialog_new ("Open File",
                                     Window,
                  //                    dialog,  
                                    GTK_FILE_CHOOSER_ACTION_OPEN,
                                      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                      NULL);

     if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
       {
         //char *filename;

         filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
           gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(dialog), TRUE);
           int i;
         // for(i=0;i<1;i++){
         // tracks[1] = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
          // filenames = gtk_file_chooser_get_uris(GTK_FILE_CHOOSER (dialog));
          
           add_to_list(treeView,filename);
         // add_to_list(treeView,tracks[1]); 
//           append(track[0],filename);
//          strcat(tracks,filename);
  
      printf("current song position:%d\n",trackPos);

       //}
       // tracks[1] = "sounds/door1.wav";
     gtk_widget_destroy (dialog);
    // add_to_list(treeView,tracks[0]);
   // add_to_list(treeView,tracks[1]);
  //test

  }


}

int clicks;


gboolean on_keypress (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    switch(event->keyval)
    {
     case GDK_KEY_z:
    
//     clicks++;
//printf("song length: %d \n",length);
//result = channel->getPosition(&ms,FMOD_TIMEUNIT_MS);
//gtk_adjustment_get_value(hadjustment);
//gtk_adjustment_set_value(hadjustment,5000);
//successfully increments slider
g_timeout_add(100, timeout_func, NULL);


//     pauseAudio();
//paused = 1;
// result = FMOD_Channel_GetPosition(&channel,&ms,FMOD_TIMEUNIT_MS);  
   break;
     case GDK_KEY_o:
    // unpauseAudio();
     openKey();
     break;
     case GDK_KEY_a:
  //   unpauseAudio();
   default:
    return FALSE;
   }
}
//test


//test
static GtkWidget *xpm_label_box( gchar     *xpm_filename,
                                 gchar     *label_text )
{
    GtkWidget *box;
    GtkWidget *label;
    GtkWidget *image;

    /* Create box for image and label */
    box = gtk_hbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);

    /* Now on to the image stuff */
    image = gtk_image_new_from_file (xpm_filename);

    /* Create a label for the button */
    label = gtk_label_new (label_text);

    /* Pack the image and label into the box */
    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
    gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 3);

    gtk_widget_show (image);
    gtk_widget_show (label);

    return box;
}

/* Our usual callback function */
static void callback( GtkWidget *widget,
                      gpointer   data )
{   
   //tes
   if(tracks[0] == NULL){
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"no file selected","failed to load",NULL);
  }
//     unpauseAudio();
  // playSound(tracks[0],SDL_MIX_MAXVOLUME /2);
  int index;
//   for(index=0;index<1;index++){
 // playMusic(tracks[0], SDL_MIX_MAXVOLUME / 1);
//     SDL_Delay(2000);
//  pauseAudio();
  //  }

}//test
//test

//test
int main( int   argc,
          char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    //GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box;
    GtkWidget *grid;
    GtkWidget *stopButton;
    GtkWidget *menubar;
  GtkWidget *fileMenu;
  GtkWidget *fileMi;
  GtkWidget *quitMi;
  GtkWidget *openMi;
  GtkWidget *vbox;
  GtkWidget *h_scale;
  GtkWidget *hlabel;
 // GtkWidget *treeView;
  GtkWidget *scrollWindow;
 // GtkAdjustment *hadjustment;
  GtkWidget *image;
  
    int flags = MIX_INIT_MP3;
    int result = 0;
Uint32 timeout = SDL_GetTicks() + 1;



    SDL_Event e;

//    SDL_Init(SDL_INIT_AUDIO);
//    initAudio();
//result = FMOD_System_Create(System);
//   FMOD_System_Init(System,FMOD_INIT_NORMAL,0,0);
//test
// result = FMOD_System_Create(&System);
// result = FMOD_System_Init(512,FMOD_INIT_NORMAL,0,extradriverdata); 
//FMOD_Main();
     //test
    gtk_init (&argc, &argv);
  //test
/*result = FMOD_System_Create(&System);
  result = FMOD_System_Init(System,1,FMOD_INIT_NORMAL,extradriverdata); 
if(result != FMOD_OK){
  printf("failed to initialize fmod!");
}
*/
//FMOD_Main();

//while(1){
 currentTime = SDL_GetTicks();
  if (currentTime > lastTime + 1000) {//1000
    printf("Report: %d\n", currentTime);
//    hadjustment = gtk_adjustment_new (currentTime, 0, 100, 5, 10, 0);
    lastTime = currentTime;
  }

//}//end while

    //test
  gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
  
     
    //test
   vbox = gtk_vbox_new(FALSE, 0);
   treeView = gtk_tree_view_new();
  //test
  hlabel = gtk_label_new ("Move the scale handle...");
  hadjustment = gtk_adjustment_new (value, 1000, 50000, 5, 10, 0);//0 50 pos 100 max 10000
  h_scale = gtk_scale_new (GTK_ORIENTATION_HORIZONTAL, hadjustment);
  gtk_scale_set_digits (GTK_SCALE (h_scale), 0); 
  gtk_widget_set_hexpand (h_scale, TRUE);
  gtk_widget_set_valign (h_scale, GTK_ALIGN_START);

  //test

   menubar = gtk_menu_bar_new();
  fileMenu = gtk_menu_new();

  fileMi = gtk_menu_item_new_with_label("File");
  quitMi = gtk_menu_item_new_with_label("Quit");
  openMi = gtk_menu_item_new_with_label("Open");

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), openMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
  //test

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (on_keypress), NULL);

    gtk_window_set_title (GTK_WINDOW (window), "Muse");
    gtk_widget_set_size_request (GTK_WIDGET (window), 200, 250);

    /* It's a good idea to do this for all windows. */
    g_signal_connect (window, "destroy",
	              G_CALLBACK (gtk_main_quit), NULL);

    g_signal_connect (window, "delete-event",
	 	      G_CALLBACK (gtk_main_quit), NULL);
   g_signal_connect (h_scale, 
                    "value-changed",//value-changed 
                    G_CALLBACK (hscale_moved), 
                    hlabel);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* Create a new button */
    button = gtk_button_new ();
    stopButton = gtk_button_new();
    grid = gtk_grid_new();
    scrollWindow = gtk_scrolled_window_new(NULL,NULL);
    image = gtk_image_new_from_file ("resources/play.jpg");

//   gtk_button_set_image (GTK_BUTTON (button), image);

//g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (my_keypress_function), NULL);
    /* Connect the "clicked" signal of the button to our callback */
    g_signal_connect (button, "clicked",
		      G_CALLBACK (callback), (gpointer) "button");

//    g_signal_connect (stopButton, "clicked",
  //                    G_CALLBACK (pauseAudio), (gpointer) "stopButton");

    g_signal_connect(G_OBJECT(quitMi), "activate",
        G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(openMi), "activate",
        G_CALLBACK(openKey), NULL);
/*    g_signal_connect (h_scale, 
                    "value-changed",//value-changed 
                    G_CALLBACK (hscale_update), 
                    hlabel);
*/


    g_signal_connect(treeView, "row-activated", (GCallback)view_onRowActivated, NULL);

//test

//test
    /* This calls our box creating function */
   // box = xpm_label_box ("info.xpm", "button");
    

    /* Pack and show all our widgets */
   // gtk_widget_show (box);
    gtk_container_add(GTK_CONTAINER(window), vbox);
   // gtk_container_add (GTK_CONTAINER (button), box);
    gtk_container_add(GTK_CONTAINER (vbox),grid);
   // gtk_grid_attach(GTK_GRID(grid),button,0,0,1,1);
  //  gtk_grid_attach(GTK_GRID(grid),stopButton,10,10,1,1);
    gtk_grid_attach (GTK_GRID (grid), h_scale, 30, 20, 1, 1);//track seek
    gtk_grid_attach (GTK_GRID (grid), hlabel,0,1,1,1);
    gtk_container_add(GTK_CONTAINER(vbox),treeView);
//    gtk_button_set_image (GTK_BUTTON (button), image);  
       
      init_list(treeView);
     // add_to_list(treeView,tracks[0]);
//    gtk_widget_show (button);
    

  //  gtk_container_add (GTK_CONTAINER (window), button);

    gtk_widget_show_all(window);


    /* Rest in gtk_main and wait for the fun to begin! */
    gtk_main ();



    return 0;
}

