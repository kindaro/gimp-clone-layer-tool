/* clone-layer tool - plugin for GIMP * /

/*
 * onExit.c
 *
 *  Created on: 30 июня 2011
 *      Author: RemyAWM
 *      http://remyawm.blogspot.com/
 */

static void onExit(GimpRunMode run_mode){
	//Remove all!
	onUndoClick();
	//Remove work layer
	if(workLayer!=-1){
		if(gimp_item_is_valid(workLayer))
				gimp_image_remove_layer(curImage,workLayer);
		workLayer=-1;
	}

	if(run_mode != GIMP_RUN_NONINTERACTIVE)
		gimp_displays_flush();

	if(!gimp_image_undo_is_enabled(curImage))
		gimp_image_undo_thaw(curImage);

	if(clonedLayersList){
	freeLayerStack(clonedLayersList);
	g_list_free(clonedLayersList);
	clonedLayersList = NULL;
	}

	gimp_drawable_flush (curDrawable);
	gimp_drawable_detach(curDrawable);

}
