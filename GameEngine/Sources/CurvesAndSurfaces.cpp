#include "CurvesAndSurfaces.h"



namespace tema1
{
	CurvesAndSurfaces::CurvesAndSurfaces(manager::ModelManager* model_manager, manager::UserInteractionManager* user_interaction_manager, manager::CameraManager* camera_manager)
	{
		this->model_manager = model_manager;
		this->user_interaction_manager = user_interaction_manager;
		this->camera_manager = camera_manager;

		this->addAxisModel();
	}

	bool CurvesAndSurfaces::isConsistent()
	{
		/* Validation */
		if (this->current_model == nullptr)
			return true;

		if (this->current_model->meshes.size() == 0)
			return true;

		switch (this->current_model->ctype)
		{
		case model::HERMITE: {
			if (this->current_model->meshes.back()->indices.size() < 4) {
				std::cout << "Need more " << 4 - this->current_model->meshes.back()->indices.size() << " hermite points to finish the curve\n";
				return false;
			}

			break;
		}
		case model::BEZIER: {
			if (this->current_model->meshes.back()->indices.size() < 4) {
				std::cout << "Need more " << 4 - this->current_model->meshes.back()->indices.size() << " bezier points to finish the curve\n";
				return false;
			}

			break;
		}
		case model::BSPLINE: {
			if (this->current_model->meshes.back()->indices.size() < 3) {
				std::cout << "Need more " << 3 - this->current_model->meshes.back()->indices.size() << " b-spline points to finish the curve\n";
				return false;
			}

			break;
		}
		case model::NURBS: {
			if (this->current_model->meshes.back()->indices.size() < 3) {
				std::cout << "Need more " << 3 - this->current_model->meshes.back()->indices.size() << " b-spline points to finish the curve\n";
				return false;
			}

			break;
		}
		case model::SPLINE: {
			if (this->current_model->meshes.back()->indices.size() < 2) {
				std::cout << "Need more " << 2 - this->current_model->meshes.back()->indices.size() << " spline points to finish the curve\n";
				return false;
			}

			break;
		}
		case model::S_SPLINE: {
			if (this->current_model->meshes.back()->indices.size() < 9) {
				std::cout << "Need more " << 9 - this->current_model->meshes.back()->indices.size() << " points to finish the spline surface\n";
				return false;
			}

			break;
		}
		case model::S_NURBS: {
			if (this->current_model->meshes.back()->indices.size() < 9) {
				std::cout << "Need more " << 9 - this->current_model->meshes.back()->indices.size() << " points to finish the nurbs surface\n";
				return false;
			}

			break;
		}
		case model::S_BEZIER: {
			if (this->current_model->meshes.back()->indices.size() < 16) {
				std::cout << "Need more " << 16 - this->current_model->meshes.back()->indices.size() << " points to finish the bezier surface\n";
				return false;
			}

			break;
		}
		}

		return true;
	}

	void CurvesAndSurfaces::startNewModelProcessing(model::CurveType curve_type)
	{
		/* Validation */
		if (this->current_model != nullptr) {
			std::cout << "Finish the current curve processing\n";
			return;
		}

		this->previous_model = nullptr;

		/* Computation */
		this->current_model = new model::ModelFormat();
		this->current_model->id = this->model_id++;
		this->current_model->ctype = curve_type;

		this->models[curve_type].push_back(this->current_model);

		this->model_manager->add(this->current_model);
	}

	void CurvesAndSurfaces::insertPoint(glm::vec3 point)
	{
		/* Validation */
		if (this->current_model == nullptr) {
			std::cout << "Select a new type of curve to be generated\n";
			return;
		}

		/* Setup a new set of control points */
		switch (this->current_model->ctype)
		{
		case model::HERMITE: {
			if (this->current_model->meshes.size() != 0)
				if (this->current_model->meshes.back()->indices.size() % 4 != 0)
					break;

			mesh::MeshFormat* mesh = new mesh::MeshFormat();

			mesh->draw_command.count = 0;
			mesh->draw_command.instance_count = 1;
			mesh->draw_command.first_index = 0;
			mesh->draw_command.base_vertex = -1;
			mesh->draw_command.base_instance = -1;

			if (this->current_model->meshes.size() > 0)
			{
				/* Computation */
				mesh->vertices.push_back(this->current_model->meshes.back()->vertices[2]);
				mesh->indices.push_back(0);
				mesh->vertices.push_back(this->current_model->meshes.back()->vertices[3]);
				mesh->indices.push_back(1);
				this->current_model->meshes.back()->draw_command.count = 2;
			}

			this->current_model->meshes.push_back(mesh);

			break;
		}

		case model::BEZIER: {
			if (this->current_model->meshes.size() != 0)
				if (this->current_model->meshes.back()->indices.size() % 4 != 0)
					break;

			mesh::MeshFormat* mesh = new mesh::MeshFormat();

			mesh->draw_command.count = 0;
			mesh->draw_command.instance_count = 1;
			mesh->draw_command.first_index = 0;
			mesh->draw_command.base_vertex = -1;
			mesh->draw_command.base_instance = -1;

			if (this->current_model->meshes.size() > 0)
			{
				/* Computation */
				mesh->vertices.push_back(vertex::VertexFormat((this->current_model->meshes.back()->vertices[3].position + this->current_model->meshes.back()->vertices[2].position) / glm::vec3(2.0, 2.0, 2.0), glm::vec3(), glm::vec2()));
				mesh->indices.push_back(0);

				mesh->vertices.push_back(this->current_model->meshes.back()->vertices[3]);
				mesh->indices.push_back(1);

				this->current_model->meshes.back()->vertices[3] = vertex::VertexFormat((this->current_model->meshes.back()->vertices[3].position + this->current_model->meshes.back()->vertices[2].position) / glm::vec3(2.0, 2.0, 2.0), glm::vec3(), glm::vec2());

				this->current_model->meshes.back()->draw_command.count = 2;
			}

			this->current_model->meshes.push_back(mesh);

			break;
		}

		case model::BSPLINE: {
			if (this->current_model->meshes.size() != 0)
				if (this->current_model->meshes.back()->indices.size() % 3 != 0)
					break;

			mesh::MeshFormat* mesh = new mesh::MeshFormat();

			mesh->draw_command.count = 0;
			mesh->draw_command.instance_count = 1;
			mesh->draw_command.first_index = 0;
			mesh->draw_command.base_vertex = -1;
			mesh->draw_command.base_instance = -1;

			if (this->current_model->meshes.size() > 0)
			{
				/* Computation */
				mesh->vertices.push_back(this->current_model->meshes.back()->vertices[1]);
				mesh->indices.push_back(0);
				mesh->vertices.push_back(this->current_model->meshes.back()->vertices[2]);
				mesh->indices.push_back(1);
				this->current_model->meshes.back()->draw_command.count = 2;
			}

			this->current_model->meshes.push_back(mesh);

			break;
		}

		case model::NURBS: {
			if (this->current_model->meshes.size() != 0)
				if (this->current_model->meshes.back()->indices.size() % 3 != 0)
					break;

			mesh::MeshFormat* mesh = new mesh::MeshFormat();

			mesh->draw_command.count = 0;
			mesh->draw_command.instance_count = 1;
			mesh->draw_command.first_index = 0;
			mesh->draw_command.base_vertex = -1;
			mesh->draw_command.base_instance = -1;

			if (this->current_model->meshes.size() > 0)
			{
				/* Computation */
				mesh->vertices.push_back(this->current_model->meshes.back()->vertices[1]);
				mesh->indices.push_back(0);
				mesh->vertices.push_back(this->current_model->meshes.back()->vertices[2]);
				mesh->indices.push_back(1);
				this->current_model->meshes.back()->draw_command.count = 2;
			}

			this->current_model->meshes.push_back(mesh);

			break;
		}

		case model::SPLINE: {
			if (this->current_model->meshes.size() != 0)
				if (this->current_model->meshes.back()->indices.size() % 2 != 0)
					break;

			mesh::MeshFormat* mesh = new mesh::MeshFormat();

			mesh->draw_command.count = 0;
			mesh->draw_command.instance_count = 1;
			mesh->draw_command.first_index = 0;
			mesh->draw_command.base_vertex = -1;
			mesh->draw_command.base_instance = -1;


			/* Create the next mesh */
			if (this->current_model->meshes.size() > 0)
			{
				/* Computation */
				mesh->vertices.push_back(this->current_model->meshes.back()->vertices[1]);
				mesh->indices.push_back(0);
				this->current_model->meshes.back()->draw_command.count = 1;
			}

			this->current_model->meshes.push_back(mesh);

			break;
		}

		case model::S_SPLINE: {
			if (this->current_model->meshes.size() == 1)
			{
				if (this->current_model->meshes[0]->indices.size() % 9 == 0)
				{
					std::cout << "Max number of points (9) for spline surface reached\n";
					return;
				}

				break;
			}

			mesh::MeshFormat* mesh = new mesh::MeshFormat();

			mesh->draw_command.count = 0;
			mesh->draw_command.instance_count = 1;
			mesh->draw_command.first_index = 0;
			mesh->draw_command.base_vertex = -1;
			mesh->draw_command.base_instance = -1;

			this->current_model->meshes.push_back(mesh);

			break;
		}

		case model::S_NURBS: {
			if (this->current_model->meshes.size() == 1)
			{
				if (this->current_model->meshes[0]->indices.size() % 9 == 0)
				{
					std::cout << "Max number of points (9) for nurbs surface reached\n";
					return;
				}

				break;
			}

			mesh::MeshFormat* mesh = new mesh::MeshFormat();

			mesh->draw_command.count = 0;
			mesh->draw_command.instance_count = 1;
			mesh->draw_command.first_index = 0;
			mesh->draw_command.base_vertex = -1;
			mesh->draw_command.base_instance = -1;

			this->current_model->meshes.push_back(mesh);

			break;
		}

		case model::S_BEZIER: {
			if (this->current_model->meshes.size() == 1)
			{
				if (this->current_model->meshes[0]->indices.size() % 16 == 0)
				{
					std::cout << "Max number of points (16) for bezier surface reached\n";
					return;
				}

				break;
			}


			mesh::MeshFormat* mesh = new mesh::MeshFormat();

			mesh->draw_command.count = 0;
			mesh->draw_command.instance_count = 1;
			mesh->draw_command.first_index = 0;
			mesh->draw_command.base_vertex = -1;
			mesh->draw_command.base_instance = -1;

			this->current_model->meshes.push_back(mesh);

			break;
		}

		}

		/* Validation */
		if (this->current_model->meshes.size() == 0) {
			std::cout << "Insert error\n";
			return;
		}

		/* Computation */
		this->current_model->meshes.back()->vertices.push_back(vertex::VertexFormat(point, glm::vec3(), glm::vec2()));
		this->current_model->meshes.back()->indices.push_back(this->current_model->meshes.back()->vertices.size() - 1);
		this->current_model->meshes.back()->draw_command.count = this->current_model->meshes.back()->indices.size();


		this->current_model->meshes.back()->extra_model_property.right_x = this->camera_manager->getPlayerCamera()->getDirectionVector().x;
		this->current_model->meshes.back()->extra_model_property.right_y = this->camera_manager->getPlayerCamera()->getDirectionVector().y;
		this->current_model->meshes.back()->extra_model_property.right_z = this->camera_manager->getPlayerCamera()->getDirectionVector().z;


		switch (this->current_model->ctype)
		{
		case model::SPLINE: {
			GLuint mesh_idx = this->current_model->meshes.size() - 1;

			/* Compute tangents of previous mesh */
			if (this->current_model->meshes.size() == 1 && this->current_model->meshes.back()->vertices.size() == 2)
			{
				this->current_model->meshes.back()->vertices.push_back(vertex::VertexFormat(this->current_model->meshes.back()->vertices[1].position - this->current_model->meshes.back()->vertices[0].position, glm::vec3(), glm::vec2()));
				this->current_model->meshes.back()->indices.push_back(2);
				this->current_model->meshes.back()->vertices.push_back(vertex::VertexFormat(this->current_model->meshes.back()->vertices[1].position - this->current_model->meshes.back()->vertices[0].position, glm::vec3(), glm::vec2()));
				this->current_model->meshes.back()->indices.push_back(3);

				this->current_model->meshes.back()->draw_command.count += 2;
			}
			else if (this->current_model->meshes.size() > 1 && this->current_model->meshes.back()->vertices.size() == 2)
			{
				this->current_model->meshes.back()->vertices.push_back(vertex::VertexFormat(this->current_model->meshes.back()->vertices[1].position - this->current_model->meshes[mesh_idx - 1]->vertices[0].position, glm::vec3(), glm::vec2()));
				this->current_model->meshes.back()->indices.push_back(2);

				this->current_model->meshes[mesh_idx - 1]->vertices[3] = vertex::VertexFormat(this->current_model->meshes.back()->vertices[1].position - this->current_model->meshes[mesh_idx - 1]->vertices[0].position, glm::vec3(), glm::vec2());

				this->current_model->meshes.back()->vertices.push_back(vertex::VertexFormat(this->current_model->meshes.back()->vertices[1].position - this->current_model->meshes.back()->vertices[0].position, glm::vec3(), glm::vec2()));
				this->current_model->meshes.back()->indices.push_back(3);

				this->current_model->meshes.back()->draw_command.count += 2;
			}

			break;
		}
		}

		
		/* Reset buffers: VBO, EBO, DIBO and SSBO */
		this->resendCurrentModelToManager();
	}

	bool CurvesAndSurfaces::canActivateEditing()
	{
		/* Validation */
		if (this->current_model != nullptr) {
			std::cout << "Finish the current curve processing\n";
			return false;
		}

		if (this->previous_model == nullptr) {
			std::cout << "No curve to be edited\n";
			return false;
		}

		return true;
	}

	void CurvesAndSurfaces::endModelProcessing()
	{
		/* Validation */
		if (!this->isConsistent())
			return;

		if (this->current_model == nullptr) {
			std::cout << "No curve under processing\n";
			return;
		}

		/* Computation */
		this->previous_model = this->current_model;
		this->current_model = nullptr;
	}

	bool CurvesAndSurfaces::isModelUnderProcessing()
	{
		return this->current_model != nullptr;
	}


	void CurvesAndSurfaces::setModelTransformation(GLuint transformation_id)
	{
		if (this->current_model == nullptr)
			return;

		if (this->current_model->meshes.size() == 0)
			return;

		this->current_model->transformation = transformation_id;

		this->current_model->curves_no = 1;

		this->resendCurrentModelToManager();

		/*if (transformation_id == 0)
			std::cout << "Trabsformation: Translation\n";
		else
			std::cout << "Trabsformation: Rotation\n";*/
	}

	void CurvesAndSurfaces::increaseCurvesNo()
	{
		if (this->current_model == nullptr)
			return;

		if (this->current_model->meshes.size() == 0)
			return;

		this->current_model->curves_no++;

		this->resendCurrentModelToManager();
	}

	void CurvesAndSurfaces::decreaseCurvesNo()
	{
		if (this->current_model == nullptr)
			return;

		if (this->current_model->meshes.size() == 0)
			return;


		if (this->current_model->curves_no > 1)
		{
			this->current_model->curves_no--;

			this->resendCurrentModelToManager();
		}
	}

	void CurvesAndSurfaces::updateCurvePointsNo(GLint no)
	{
		if (this->current_model == nullptr)
			return;

		if (this->current_model->meshes.size() == 0)
			return;

		if (this->current_model->curve_points_no + no > 1)
			this->current_model->curve_points_no += no;
		else
			this->current_model->curve_points_no = 1;

		this->resendCurrentModelToManager();
	}


	void CurvesAndSurfaces::setCurrentModel(model::ModelFormat* model)
	{
		if (this->current_model != nullptr)
		{
			std::cout << "Another model under processing\n";
		}

		this->current_model = model;
	}

	void CurvesAndSurfaces::addAxisModel()
	{
		model::ModelFormat* model = new model::ModelFormat();
		model->id = 0;
		model->ctype = model::AXIS;

		mesh::MeshFormat* mesh = new mesh::MeshFormat();

		mesh->draw_command.count = 0;
		mesh->draw_command.instance_count = 1;
		mesh->draw_command.first_index = 0;
		mesh->draw_command.base_vertex = -1;
		mesh->draw_command.base_instance = -1;

		mesh->vertices.push_back(vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2()));
		mesh->indices.push_back(0);
		mesh->vertices.push_back(vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2()));
		mesh->indices.push_back(1);

		mesh->vertices.push_back(vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2()));
		mesh->indices.push_back(2);
		mesh->vertices.push_back(vertex::VertexFormat(glm::vec3(), glm::vec3(), glm::vec2()));
		mesh->indices.push_back(3);

		mesh->draw_command.count = mesh->indices.size();

		model->meshes.push_back(mesh);

		this->model_manager->add(model);
		this->axis_model = model;
	}

	model::ModelFormat* CurvesAndSurfaces::getAxisModel()
	{
		return this->axis_model;
	}

	void CurvesAndSurfaces::clean()
	{
		/* Clean all the curves saved until now and also OpenGL buffers */
		typedef std::map<model::CurveType, std::vector<model::ModelFormat*>>::iterator it_type;
		for (it_type iterator = this->models.begin(); iterator != this->models.end(); iterator++) {
			for (model::ModelFormat* model : iterator->second)
				delete model;

			iterator->second.clear();
		}

		this->models.clear();

		this->current_model = nullptr;

		this->model_id = 1;

		this->model_manager->add(this->axis_model);
	}

	std::map<model::CurveType, std::vector<model::ModelFormat*>>& CurvesAndSurfaces::getModels()
	{
		return this->models;
	}

	void CurvesAndSurfaces::resendModelToManager(model::ModelFormat* model)
	{
		if (model != nullptr)
			this->model_manager->update(model);
	}

	void CurvesAndSurfaces::resendCurrentModelToManager()
	{
		if (this->current_model != nullptr)
			this->model_manager->update(this->current_model);
	}

	void CurvesAndSurfaces::printCurrentModelInfo()
	{
		if (this->current_model == nullptr) {
			std::cout << "No model to show info for\n";
			return;
		}

		std::cout << "\n\n<-------- Current Model Info -------->\n";
		std::cout << "Model type: ";

		switch (this->current_model->ctype) {
		case model::HERMITE:
			std::cout << "Hermite curve\n";
			break;
		case model::BEZIER:
			std::cout << "Bezier curve\n";
			break;
		case model::SPLINE:
			std::cout << "Spline curve\n";
			break;
		case model::BSPLINE:
			std::cout << "B-spline curve\n";
			break;
		case model::NURBS:
			std::cout << "Nurb curve\n";
			break;
		case model::S_BEZIER:
			std::cout << "Bezier Surface\n";
			break;
		case model::S_SPLINE:
			std::cout << "Spline Surface\n";
			break;
		case model::S_NURBS:
			std::cout << "Nurb surface\n";
			break;
		}
		
		std::cout << "Curves number: " << this->current_model->curves_no << std::endl;
		std::cout << "Curve points number: " << this->current_model->curve_points_no << std::endl;

		if (this->current_model->transformation == 0)
			std::cout << "Transformation: translation\n";
		else
			std::cout << "Transformation: rotation\n";

		std::cout << "<------------------------------------>\n\n";
	}
}