#pragma once

#include "defcs.h"



///	<summary>
///		Contains a series of specific data structures for the engine
///	</summary>
namespace ds
{
	///	<summary> Segment into an array 2d texture buffer </summary>
	///	<remarks> Segments are organized in a quaternary tree. Each segment represent a node </remarks>
	struct a2dtbt_seg
	{
		/// <summary> Unique integer for segment identification </summary>
		GLuint id;

		/// <summary> Texture size in width and height (square texture size) </summary>
		GLushort tex_size;

		/// <summary> X offset in the texture buffer </summary>
		GLushort x_coord;

		/// <summary> Y offset in the texture buffer </summary>
		GLushort y_coord;

		/// <summary> Z offset in the texture buffer (layer into the 2d array texture buffer) </summary>
		GLushort layer;

		/// <summary> Parent segment </summary>
		a2dtbt_seg *parent = nullptr;

		/// <summary> Sub-segments </summary>
		a2dtbt_seg *children[4];

		/// <summary>
		///		byte = 000e dcba
		///			-> e bit is set if there is no sub-segment occupied
		///			-> d/c/b/a bit is set if the fourth/third/second/first sub-segment is available
		///	</summary>
		GLubyte available_children_paths = 0x1F;
	};

	///	<summary>
	///		Manages a 2d array texture buffer with the help of a quaternary tree.
	///		Tree is STATIC -> build when class is initialized;
	///	</summary>
	///	<remarks>
	///		This class works only with one layer -> all segments will have the same value for layer member.
	///		With every tree height increase, a segment is split into other 4 sub-segments.
	///	</remarks>
	class Array2DTextureBufferTree
	{
	private:
		/// <summary> Maximum 2d texture size </summary>
		///	<remarks> This is also the maximum size of the layer (in length and width) </remarks>
		GLuint max_texture_size;

		/// <summary> Minimum 2d texture size </summary>
		///	<remarks>
		///		This gives us the height of the tree. We need to compute how many times
		///	do we need to split a segment to reach that minimum value
		///	</remarks>
		GLuint min_texture_size;

		/// <summary> Depth/Height of the tree </summary>
		GLuint height = 0;

		/// <summary> Layer in the array 2d texture buffer to be processed </summary>
		GLuint layer;

		/// <summary> Total number of tree nodes/segments </summary>
		GLuint no_of_segments = 0;

		/// <summary> Array of tree segments </summary>
		/// <remarks> a2dtbt_seg id is used as an index in the array </remarks>
		ds::a2dtbt_seg *tree_segments;

		/// <summary> Tree root </summary>
		ds::a2dtbt_seg *tree;

		/// <summary> Build the entire tree structure </summary>
		void build();

		/// <summary> Build a tree segment node </summary>
		///	<param name='parent'> Parent of the segment node to be build </param>
		///	<param name='node'> Segment node to be build </param>
		///	<param name='tex_size'> Segment texture size </param>
		///	<param name='x_coord'> X segment offset in the texture buffer </param>
		///	<param name='y_coord'> Y segment offset in the texture buffer </param>
		///	<param name='nodes_idx'> Index of a free segment from "tree_segments" array </param>
		///	<param name='height'> Current height in the tree </param>
		void buildSegment(ds::a2dtbt_seg *parent, ds::a2dtbt_seg *node, GLuint tex_size, GLuint x_coord, GLuint y_coord, GLuint *nodes_idx, GLuint height);

		/// <summary> Search for a segment of size "tex_size" </summary>
		///	<remarks> Helper for search(...) function </remarks>
		///	<param name='node'> Segment node where searching occur </param>
		///	<param name='tex_size'> Segment texture size to search for </param>
		///	<param name='height'> Current height in the tree </param>
		/// <returns> If a segment is found, returns the segment; else nullptr </returns>
		ds::a2dtbt_seg* searchSegment(ds::a2dtbt_seg *node, GLuint tex_size, GLuint height);

		/// <summary> Free a texture buffer segment </summary>
		///	<remarks> Helper for free(...) function </remarks>
		///	<param name='node'> Segment node to be freed </param>
		void freeSegment(ds::a2dtbt_seg *node);

	public:
		/// <summary> Default Constructor. Does nothing </summary>
		Array2DTextureBufferTree();

		/// <summary> Initializing constructor </summary>
		///	<param name='max_texture_size'> Maximum 2d texture size </param>
		///	<param name='min_texture_size'> Minimum 2d texture size </param>
		///	<param name='layer'> Layer in the array 2d texture buffer </param>
		Array2DTextureBufferTree(GLuint max_texture_size, GLuint min_texture_size, GLuint layer);

		/// <summary> Search for a free texture buffer segment of size "tex_size" </summary>
		///	<param name='tex_size'> Segment texture size to search for </param>
		/// <returns> If a segment is found, returns the segment; else nullptr </returns>
		ds::a2dtbt_seg* search(GLuint tex_size);

		/// <summary> Free a texture buffer segment </summary>
		///	<param name='node_id'> Id of the segment node to be freed </param>
		void free(GLuint node_id);
	};
}