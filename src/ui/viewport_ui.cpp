#include "viewport_ui.h";
#include "iostream"

ViewportUI::ViewportUI(Framebuffer* buffer, GizmoUI* gizmo)
{
	printf("ViewportUI\n");
	this->buffer = buffer;
	this->gizmo = gizmo;
}

void ViewportUI::DrawUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");
	ImVec2 viewportSize = ImGui::GetContentRegionAvail();
	auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
	auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
	auto viewportOffset = ImGui::GetWindowPos();
	viewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
	viewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
	
	screenSize = buffer->GetScreenSize();
	if(screenSize->x != viewportSize.x || screenSize->y != viewportSize.y)
		buffer->Resize(viewportSize.x, viewportSize.y);
	unsigned int textureID = *buffer->GetColorAttachment();
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	gizmo->DrawGizmo(viewportBounds);
	ImGui::PopStyleVar();
	ImGui::End();
}