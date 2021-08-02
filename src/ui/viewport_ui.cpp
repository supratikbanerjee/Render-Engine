#include "viewport_ui.h";

ViewportUI::ViewportUI(Framebuffer* buffer)
{
	this->buffer = buffer;
}

void ViewportUI::DrawUI()
{
	ImGui::Begin("Viewport");
	ImVec2 viewportSize = ImGui::GetContentRegionAvail();
	screenSize = buffer->GetScreenSize();
	if(screenSize->x != viewportSize.x || screenSize->y != viewportSize.y)
		buffer->Resize(viewportSize.x, viewportSize.y);
	unsigned int textureID = *buffer->GetColorAttachment();
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	ImGui::End();
}