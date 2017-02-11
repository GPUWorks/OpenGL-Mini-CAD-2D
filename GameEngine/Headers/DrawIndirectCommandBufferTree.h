#pragma once

#include "defcs.h"



///	<summary>
///		Contains a series of specific data structures for the engine
///	</summary>
namespace ds
{
	///	<summary> Segment into a "draw indirect commands" buffer </summary>
	///	<remarks> Segments are organized in a binary tree. Each segment represent a node </remarks>
	struct dicbt_seg
	{
		/// <summary> Unique integer for segment identification </summary>
		GLuint id;

		/// <summary> Offset in the buffer </summary>
		GLuint offset;

		/// <summary> Number of "draw indirect commands" the segment covers </summary>
		GLuint commands_no;

		/// <summary> Parent segment </summary>
		dicbt_seg *parent = nullptr;

		/// <summary> Sub-segments </summary>
		dicbt_seg *children[2];

		/// <summary>
		///		byte = 000e 00ba
		///			-> e bit is set if there is no sub-segment occupied
		///			-> b/a bit is set if the second/first sub-segment is available
		///	</summary>
		GLubyte available_children_paths = 0x13;
	};


	///	<summary>
	///		Manages a buffer containing "draw indirect commands" with the help of a binary tree.
	///		Tree is STATIC -> build when class is initialized;
	///	</summary>
	///	<remarks>
	///		With every tree height increase, a segment is split into other 2 sub-segments.
	///	</remarks>
	class DrawIndirectCommandBufferTree
	{
	private:
		/// <summary> Maximum "draw indirect commands" in the buffer </summary>
		GLuint max_commands_no;

		/// <summary> Minimum "draw indirect commands" covered by a segment </summary>
		///	<remarks>
		///		This gives us the height of the tree. We need to compute how many times
		///	do we need to split a segment to reach that minimum value
		///	</remarks>
		GLuint min_commands_no;

		/// <summary> Depth/Height of the tree </summary>
		GLuint height = 0;

		/// <summary> Total number of tree nodes/segments </summary>
		GLuint no_of_segments = 0;

		/// <summary> Array of tree segments </summary>
		/// <remarks> dicbt_seg id is used as an index in the array </remarks>
		ds::dicbt_seg *tree_segments;

		/// <summary> Tree root </summary>
		ds::dicbt_seg *tree;

		/// <summary> Build the entire tree structure </summary>
		void build();

		/// <summary> Build a tree segment node </summary>
		///	<param name='parent'> Parent of the segment node to be build </param>
		///	<param name='node'> Segment node to be build </param>
		///	<param name='offset'> Segment offset in the "draw indirect commands" buffer </param>
		///	<param name='commands_no'> Number of "draw indirect commands" the segment covers </param>
		///	<param name='nodes_idx'> Index of a free segment from "tree_segments" array </param>
		///	<param name='height'> Current height in the tree </param>
		void buildSegment(ds::dicbt_seg *parent, ds::dicbt_seg *node, GLuint offset, GLuint commands_no, GLuint *nodes_idx, GLuint height);

		/// <summary> Search for a segment containing "commands_no" commands. </summary>
		///	<remarks> Helper for search(...) function </remarks>
		///	<param name='node'> Segment node where searching occur </param>
		///	<param name='commands_no'> Number of free "draw indirect commands" to search for </param>
		///	<param name='height'> Current height in the tree </param>
		/// <returns> If a segment is found, returns the segment; else nullptr </returns>
		ds::dicbt_seg* searchSegment(ds::dicbt_seg *node, GLuint commands_no, GLuint height);

		/// <summary> Free a buffer segment </summary>
		///	<remarks> Helper for free(...) function </remarks>
		///	<param name='node'> Segment node to be freed </param>
		void freeSegment(ds::dicbt_seg *node);

	public:
		/// <summary> Default Constructor. Does nothing </summary>
		DrawIndirectCommandBufferTree();

		/// <summary> Initializing constructor </summary>
		///	<param name='max_commands_no'> Maximum "draw indirect commands" in the buffer </param>
		///	<param name='min_commands_no'> Minimum "draw indirect commands" in the buffer </param>
		DrawIndirectCommandBufferTree(GLuint max_commands_no, GLuint min_commands_no);

		/// <summary> Search for a free buffer segment containing "commands_no" commands </summary>
		///	<param name='commands_no'> Number of free "draw indirect commands" to search for </param>
		/// <returns> If a segment is found, returns the segment; else nullptr </returns>
		ds::dicbt_seg* search(GLuint commands_no);

		/// <summary> Free a buffer segment </summary>
		///	<param name='node_id'> Id of the segment node to be freed </param>
		void free(GLuint node_id);

		void clean();
	};
}