#pragma once

#include "defcs.h"



///	<summary>
///		Contains a series of specific data structures for the engine
///	</summary>
namespace ds
{
	struct vbt_seg
	{
		GLuint id;

		GLuint offset;

		GLuint vertices_no;

		vbt_seg *parent = nullptr;

		vbt_seg *children[2];

		GLubyte available_children_paths = 0x13;
	};


	
	class VertexBufferTree
	{
	private:
		GLuint max_vertices_no;

		
		GLuint min_vertices_no;

		GLuint height = 0;

		GLuint no_of_segments = 0;

		
		ds::vbt_seg *tree_segments;

		ds::vbt_seg *tree;

		void build();

		
		void buildSegment(ds::vbt_seg *parent, ds::vbt_seg *node, GLuint offset, GLuint vertices_no, GLuint *nodes_idx, GLuint height);

		
		ds::vbt_seg* searchSegment(ds::vbt_seg *node, GLuint vertices_no, GLuint height);

	
		void freeSegment(ds::vbt_seg *node);

	public:
		VertexBufferTree();

		VertexBufferTree(GLuint max_vertices_no, GLuint min_vertices_no);

		ds::vbt_seg* search(GLuint vertices_no);

		void free(GLuint node_id);

		void clean();
	};
}