#include "gizmo_ui.h"
#include "iostream"

GizmoUI::GizmoUI(SceneManager* scene)
{
	printf("GizmoUI\n");
	this->scene = scene;
}

void GizmoUI::Begin()
{
	ImGuizmo::BeginFrame();
}

void GizmoUI::DrawGizmo(glm::vec2 viewportBounds[])
{
	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetDrawlist();

	ImGuizmo::SetRect(viewportBounds[0].x, viewportBounds[0].y, viewportBounds[1].x - viewportBounds[0].x, viewportBounds[1].y - viewportBounds[0].y);

	glm::mat4* cameraProjection = scene->GetMainCamera()->GetProjectionMatrix();
	glm::mat4* cameraView = scene->GetMainCamera()->GetViewMatrix();

	Model* selected = (Model*)scene->getActiveModel();
	glm::mat4 transform = selected->getTransform()->model;
	ImGuizmo::Manipulate(glm::value_ptr(*cameraView), glm::value_ptr(*cameraProjection),
		(ImGuizmo::OPERATION)gizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform));

	if (ImGuizmo::IsUsing())
	{
		selected->getTransform()->translation = glm::vec3(transform[3]);

		glm::decompose(transform, scale, rotation, translation, skew, perspective);
		euler = glm::eulerAngles(rotation);

		deltaRotation = euler - selected->getTransform()->rotation;
		selected->getTransform()->translation = translation;
		selected->getTransform()->rotation += deltaRotation;
		selected->getTransform()->scale = scale;
	}

}