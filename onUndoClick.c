/* clone-layer tool - plugin for GIMP * /

/*
 * onUndoClick.c
 *
 *  Created on: 30 июня 2011
 *      Author: RemyAWM
 *      http://remyawm.blogspot.com/
 */

static void onUndoClick(){
	//remove all
	LayerStack *rl;
	GList *l;
	for(l = g_list_last(clonedLayersList); l; l = l->prev){
		rl = l->data;
		gimp_image_remove_layer(curImage,rl->id);
		g_free(l->data);
	}
	g_list_free(clonedLayersList);
	clonedLayersList=NULL;

	groupLayer = -1;

	if(!createWorkLayer(curDrawable)){
		g_printf("onUndoClick -> cannot create new workLayer!");
		return;
	}

	gimp_displays_flush();
}
