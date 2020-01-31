/* clone-layer tool - plugin for GIMP * /

/*
 * run.c
 *
 *  Created on: 30 июня 2011
 *      Author: RemyAWM
 *      http://remyawm.blogspot.com/
 */

#include "clone-layer-tool.h"
#include "dialog.c"

static void run (const gchar *name,
				gint nparams,
				const GimpParam  *param,
				gint *nreturn_vals,
				GimpParam **return_vals
				)
{

  static GimpParam  values[2];

  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GimpRunMode       run_mode;
  GimpDrawable     *drawable;
  gint32 			image;

  *nreturn_vals = 1; // кол-во эл. в массиве return_vals
  *return_vals  = values; // Возвращает всегда статус GIMP_PDB_SUCCESS

  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;
  values[1].type = GIMP_PDB_LAYER;
  values[1].data.d_layer = -1;

  /* Узнаем в каком режиме вызван плагин.
   * Возможны варианты -
   * 	GIMP_RUN_INTERACTIVE - с вызовом диалога плагина
   * 	GIMP_RUN_NONINTERACTIVE - выполнить без диалога
   * 	GIMP_RUN_WITH_LAST_VALS - выполнить плагин с диалогом и последними использоваными зачениями
   */

  run_mode = param[0].data.d_int32;

  drawable = gimp_drawable_get(param[2].data.d_drawable);
   /*image = gimp_item_get_image(drawable->drawable_id);*/
  image = param[1].data.d_image;

  curDrawable=drawable;
  curImage = image;

  //Плагин может работать только со слоями!
  //Проверяем является ли текущий drawable слоем:
  if(!gimp_item_is_layer(drawable->drawable_id)){
	  status = GIMP_PDB_EXECUTION_ERROR;
	  gimp_message("CloneTool Error: \n This plugin works with layer only! \nPlease, select layer and try again.");
	  onExit(run_mode);
	  return;
  }

  /* initialize random seed: */
  //	srand(time(NULL));
    grnd = g_rand_new ();

  gimp_image_undo_freeze(curImage);

  //Try to make workLayer...
  if(!createWorkLayer(curDrawable)){
	  status = GIMP_PDB_EXECUTION_ERROR;
	  onExit(run_mode);
	  return;
  }


  initVals();

  switch(run_mode)
    {
    case GIMP_RUN_INTERACTIVE:
      gimp_get_data (PLUG_IN_PROC, &pl_vals);

      if (!clone_dialog()){
    	  onExit(run_mode);
    	  return;
      }
      break;

    case GIMP_RUN_NONINTERACTIVE:
    	  status = GIMP_PDB_CALLING_ERROR;
    	  g_printf("%s doesn't run in NONINTERACTIVE mode!", PLUG_IN_PROC);
    break;

    case GIMP_RUN_WITH_LAST_VALS:
      /*  Get last values if needed  */
      gimp_get_data(PLUG_IN_PROC, &pl_vals);
      gimp_context_set_interpolation(pl_vals.interpolation);
      onCloneClick();
      break;

    default:
      break;
    }

  if (status == GIMP_PDB_SUCCESS){

	  onSuccess(); //Apply all changes before plugin closed
	  if (run_mode != GIMP_RUN_NONINTERACTIVE)
		  gimp_displays_flush ();

	  if (run_mode == GIMP_RUN_INTERACTIVE || run_mode == GIMP_RUN_WITH_LAST_VALS)
	            gimp_set_data (PLUG_IN_PROC, &pl_vals, sizeof (MyCloneVals));

  }
  else
	  status = GIMP_PDB_EXECUTION_ERROR;

  if(clonedLayersList){
	  freeLayerStack(clonedLayersList);
	  g_list_free(clonedLayersList);
	  clonedLayersList = NULL;
  }

  gimp_image_undo_thaw(curImage);

  gimp_drawable_flush (drawable);
  gimp_drawable_detach(curDrawable);

  values[0].data.d_status = status;
}
