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
bool isActivated = false;

// --- Логика меню ---
void DrawMenu() {
    if (!isActivated) {
        if (ImGui::Button("God", ImVec2(100, 40))) {
            isActivated = true;
        }
    } else {
        ImGui::TextColored(ImVec4(0, 1, 0.5f, 1), "Godcheting активирован");
        ImGui::Separator();
        ImGui::Text("Версия:");
        if (ImGui::Button("Free", ImVec2(-1, 40))) { FreeVersion = true; PaidVersion = false; }
        if (ImGui::Button("Paid (нужен ключ)", ImVec2(-1, 40))) { PaidVersion = true; FreeVersion = false; }

        if (FreeVersion) { ImGui::Text("Free version active"); }
        if (PaidVersion) { ImGui::Text("Paid version - ключ в ТГК автора"); }
    }
}

// --- Функции LGL (заменяют Menu.cpp) ---
void Init(JNIEnv *env, jobject thiz, jobject ctx, jobject title, jobject subtitle) {
    setText(env, title, OBFUSCATE("<b>Godcheat</b>"));
    setText(env, subtitle, OBFUSCATE("<b>Counter Flame</b>"));
}

jstring Icon(JNIEnv *env, jobject thiz) {
    return nullptr;
}

jobjectArray SettingsList(JNIEnv *env, jobject activityObject) {
    jobjectArray ret;
    const char *features[] = {
            OBFUSCATE("Category_Godcheat"),
            OBFUSCATE("0_Button_Активировать Godcheat"),
            OBFUSCATE("Category_Версия"),
            OBFUSCATE("1_Toggle_Free Version"),
            OBFUSCATE("2_Toggle_Paid Version (ключ в ТГК)"),
    };
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray) env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")), env->NewStringUTF(""));
    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return (ret);
}

// --- Точка входа ---
void *menu_thread(void *) {
    return nullptr;
}

__attribute__((constructor))
void lib_main() {
    pthread_t ptid;
    pthread_create(&ptid, NULL, menu_thread, NULL);
}
