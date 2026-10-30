// language: C++, file: Main.cpp, target: Android NDK
#include <jni.h>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "Menu/Menu.h"

bool FreeVersion = false;
bool PaidVersion = false;

// Главное меню
void DrawMenu() {
    static bool activated = false;
    static bool showWelcome = false;

    if (!activated) {
        ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 50);
        if (ImGui::Button("God", ImVec2(100, 40))) {
            activated = true;
            showWelcome = true;
        }
        ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 60);
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
        }

        if (PaidVersion) {
            ImGui::Separator();
            ImGui::TextColored(ImVec4(1, 0.4f, 0.4f, 1), "Paid version — locked");
            ImGui::TextWrapped("Ключ у автора чита. Читай Telegram-канал автора — там ключ и код платной версии.");
        }
    }
}

// Поток для отрисовки (именно его не хватало)
void *menu_thread(void *) {
    while (true) {
        // Инициализация и отрисовка меню (зависит от шаблона LGL)
        if (isMenuOpen) {
            DrawMenu();
        }
        sleep(1);
    }
    return nullptr;
}

// Точка входа
__attribute__((constructor))
void lib_main() {
    pthread_t ptid;
    pthread_create(&ptid, NULL, menu_thread, NULL);
}
