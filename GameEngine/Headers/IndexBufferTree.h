#pragma once

#include "defcs.h"



///	<summary>
///		Contains a series of specific data structures for the engine
///	</summary>
namespace ds
{
	///	<summary> Segment into an "index" buffer </summary>
	///	<remarks> Segments are organized in a binary tree. Each segment represent a node </remarks>
	struct ibt_seg
	{
		/// <summary> Unique integer for segment identification </summary>
		GLuint id;

		/// <summary> Offset in the buffer </summary>
		GLuint offset;

		/// <summary> Number of "indices" the segment covers </summary>
		GLuint indices_no;

		/// <summary> Parent segment </summary>
		ibt_seg *parent = nullptr;

		/// <summary> Sub-segments </summary>
		ibt_seg *children[2];

		/// <summary>
		///		byte = 000e 00ba
		///			-> e bit is set if there is no sub-segment occupied
		///			-> b/a bit is set if the second/first sub-segment is available
		///	</summary>
		GLubyte available_children_paths = 0x13;
	};


	///	<summary>
	///		Manages a buffer containing "indices" with the help of a binary tree.
	///		Tree is STATIC -> build when class is initialized;
	///	</summary>
	///	<remarks>
	///		With every tree height increase, a segment is split into other 2 sub-segments.
	///	</remarks>
	class IndexBufferTree
	{
	private:
		/// <summary> Maximum "indices" in the buffer </summary>
		GLuint max_indices_no;

		/// <summary> Minimum "indices" covered by a segment </summary>
		///	<remarks>
		///		This gives us the height of the tree. We need to compute how many times
		///	do we need to split a segment to reach that minimum value
		///	</remarks>
		GLuint min_indices_no;

		/// <summary> Depth/Height of the tree </summary>
		GLuint height = 0;

		/// <summary> Total number of tree nodes/segments </summary>
		GLuint no_of_segments = 0;

		/// <summary> Array of tree nodes </summary>
		/// <remarks> ibt_seg id is used as an index in the array </remarks>
		ds::ibt_seg *tree_segments;

		/// <summary> Tree root </summary>
		ds::ibt_seg *tree;

		/// <summary> Build the entire tree structure </summary>
		void build();

		/// <summary> Build a tree segment node </summary>
		///	<param name='parent'> Parent of the segment node to be build </param>
		///	<param name='node'> Segment node to be build </param>
		///	<param name='offset'> Segment offset in the "index" buffer </param>
		///	<param name='indices_no'> Number of "indices" the segment covers </param>
		///	<param name='nodes_idx'> Index of a free segment from "tree_segments" array </param>
		///	<param name='height'> Current height in the tree </param>
		void buildSegment(ds::ibt_seg *parent, ds::ibt_seg *node, GLuint offset, GLuint indices_no, GLuint *nodes_idx, GLuint height);

		/// <summary> Search for a segment containing "indices_no" commands. </summary>
		///	<remarks> Helper for search(...) function </remarks>
		///	<param name='node'> Segment node where searching occur </param>
		///	<param name='indices_no'> Number of free "indices" to search for </param>
		///	<param name='height'> Current height in the tree </param>
		/// <returns> If a segment is found, returns the segment; else nullptr </returns>
		ds::ibt_seg* searchSegment(ds::ibt_seg *node, GLuint indices_no, GLuint height);

		/// <summary> Free a buffer segment </summary>
		///	<remarks> Helper for free(...) function </remarks>
		///	<param name='node'> Segment node to be freed </param>
		void freeSegment(ds::ibt_seg *node);

	public:
		/// <summary> Default Constructor. Does nothing </summary>
		IndexBufferTree();

		/// <summary> Initializing constructor </summary>
		///	<param name='max_indices_no'> Maximum "indices" in the buffer </param>
		///	<param name='min_indices_no'> Minimum "indices" in the buffer </param>
		IndexBufferTree(GLuint max_indices_no, GLuint min_indices_no);

		/// <summary> Search for a free buffer segment containing "indices_no" commands </summary>
		///	<param name='indices_no'> Number of free "indices" to search for </param>
		/// <returns> If a segment is found, returns the segment; else nullptr </returns>
		ds::ibt_seg* search(GLuint indices_no);

		/// <summary> Free a buffer segment </summary>
		///	<param name='node_id'> Id of the segment node to be freed </param>
		void free(GLuint node_id);

		void clean();
	};
}