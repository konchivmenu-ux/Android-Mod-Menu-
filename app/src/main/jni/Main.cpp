// language: C++, file: Main.cpp, target: Android NDK
// *LGL Mod Menu template with God circle*

#include <jni.h>
#include <string>
#include <unistd.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "Menu/Menu.h"

// Здесь будут оффсеты (пока заглушки)
bool GodMode = false;
bool FreeVersion = false;
bool PaidVersion = false;

void DrawMenu() {
    static bool activated = false;
    static bool showWelcome = false;

    if (!activated) {
        // Рисуем круг God
        if (ImGui::Button("God", ImVec2(100, 40))) {
            activated = true;
            showWelcome = true;
        }
        ImGui::TextDisabled("нажми для активации");
    } else {
        if (showWelcome) {
            ImGui::TextColored(ImVec4(0, 1, 0.5f, 1), "Godcheting активирован");
            ImGui::Separator();
        }

        ImGui::Text("Версия:");
        if (ImGui::Button("Free", ImVec2(-1, 40))) { 
            FreeVersion = true; 
            PaidVersion = false; 
            showWelcome = false; 
        }
        if (ImGui::Button("Paid (нужен ключ)", ImVec2(-1, 40))) { 
            PaidVersion = true; 
            FreeVersion = false; 
            showWelcome = false; 
        }

        if (FreeVersion) {
            ImGui::Separator();
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "Free version active");
            ImGui::TextWrapped("Базовые фичи работают. Расширение — по offsets сборки.");
            // ТУТ БУДУТ ХУКИ ПАМЯТИ (ЧИТЫ)
        }

        if (PaidVersion) {
            ImGui::Separator();
            ImGui::TextColored(ImVec4(1, 0.4f, 0.4f, 1), "Paid version — locked");
            ImGui::TextWrapped("Ключ у автора чита. Читай Telegram-канал автора — там ключ и код платной версии.");
        }
    }
}

// Точка входа в мод-меню
__attribute__((constructor))
void lib_main() {
    // Запускаем поток отрисовки меню
    pthread_t ptid;
    pthread_create(&ptid, NULL, menu_thread, NULL);
}
