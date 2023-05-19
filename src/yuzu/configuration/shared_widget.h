#pragma once

#include "yuzu/configuration/configuration_shared.h"
#include "yuzu/configuration/shared_translation.h"

class QPushButton;
class QSpinBox;
class QComboBox;
class QLineEdit;
class QSlider;
class QCheckBox;
class QLabel;
class QHBoxLayout;
class QDateTimeEdit;

namespace Settings {
class BasicSetting;
}

namespace ConfigurationShared {

enum class RequestType {
    Default,
    ComboBox,
    SpinBox,
    Slider,
    ReverseSlider,
    LineEdit,
    HexEdit,
    DateTimeEdit,
    MaxEnum,
};

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(Settings::BasicSetting* setting, const TranslationMap& translations,
           const ComboboxTranslationMap& combobox_translations, QWidget* parent, bool runtime_lock,
           std::forward_list<std::function<void(bool)>>& apply_funcs_,
           RequestType request = RequestType::Default, bool managed = true, float multiplier = 1.0f,
           Settings::BasicSetting* other_setting = nullptr,
           const QString& string = QStringLiteral(""));
    virtual ~Widget();

    bool Valid();

    [[nodiscard]] static QPushButton* CreateRestoreGlobalButton(bool using_global, QWidget* parent);

    QPushButton* restore_button{};
    QLineEdit* line_edit{};
    QSpinBox* spinbox{};
    QCheckBox* checkbox{};
    QSlider* slider{};
    QComboBox* combobox{};
    QDateTimeEdit* date_time_edit{};

private:
    QLabel* CreateLabel(const QString& text);
    QHBoxLayout* CreateCheckBox(Settings::BasicSetting* bool_setting, const QString& label,
                                std::function<void()>& load_func, bool managed);

    void CreateCombobox(const QString& label, std::function<void()>& load_func, bool managed,
                        Settings::BasicSetting* const other_setting = nullptr);
    void CreateLineEdit(const QString& label, std::function<void()>& load_func, bool managed,
                        Settings::BasicSetting* const other_setting = nullptr);
    void CreateHexEdit(const QString& label, std::function<void()>& load_func, bool managed,
                       Settings::BasicSetting* const other_setting = nullptr);
    void CreateSlider(const QString& label, bool reversed, float multiplier,
                      std::function<void()>& load_func, bool managed, const QString& format,
                      Settings::BasicSetting* const other_setting = nullptr);
    void CreateDateTimeEdit(const QString& label, std::function<void()>& load_func, bool managed,
                            bool restrict, Settings::BasicSetting* const other_setting = nullptr);
    void CreateSpinBox(const QString& label, std::function<void()>& load_func, bool managed,
                       const QString& suffix, Settings::BasicSetting* other_setting = nullptr);

    QWidget* parent;
    const TranslationMap& translations;
    const ComboboxTranslationMap& combobox_enumerations;
    Settings::BasicSetting& setting;
    std::forward_list<std::function<void(bool)>>& apply_funcs;

    bool created{false};
    bool runtime_lock{false};
};

} // namespace ConfigurationShared
