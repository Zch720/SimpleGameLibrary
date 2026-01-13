#include <gtest/gtest.h>
#include "../../include/sgf/platform/input/input.h"
#include "../../internal_include/sgf/platform/input/keyboard_input_injector.h"
#include "../../internal_include/sgf/platform/input/mouse_input_injector.h"

using namespace sgf_core;

class InputSuite: public testing::Test {
};

TEST_F(InputSuite, BeginFrame) {
    Input input;
    KeyboardInputInjector injector(input.Keyboard());

    injector.beginFrame();

    for (int i = static_cast<int>(Key::FIRST); i <= static_cast<int>(Key::LAST); i++) {
        ASSERT_FALSE(input.Keyboard().isKeyDown(static_cast<Key>(i)));
        ASSERT_FALSE(input.Keyboard().isKeyHold(static_cast<Key>(i)));
        ASSERT_FALSE(input.Keyboard().isKeyUp(static_cast<Key>(i)));
    }
}

TEST_F(InputSuite, GetKeyDown_A) {
    Input input;
    KeyboardInputInjector injector(input.Keyboard());

    injector.beginFrame();
    injector.onKeyPressed(Key::A);
    
    ASSERT_TRUE(input.Keyboard().isKeyDown(Key::A));
    ASSERT_TRUE(input.Keyboard().isKeyHold(Key::A));
    ASSERT_FALSE(input.Keyboard().isKeyUp(Key::A));
}

TEST_F(InputSuite, GetKeyPress_A) {
    Input input;
    KeyboardInputInjector injector(input.Keyboard());

    injector.beginFrame();
    injector.onKeyPressed(Key::A);
    
    ASSERT_TRUE(input.Keyboard().isKeyDown(Key::A));
    ASSERT_TRUE(input.Keyboard().isKeyHold(Key::A));
    ASSERT_FALSE(input.Keyboard().isKeyUp(Key::A));

    injector.beginFrame();
    
    ASSERT_FALSE(input.Keyboard().isKeyDown(Key::A));
    ASSERT_TRUE(input.Keyboard().isKeyHold(Key::A));
    ASSERT_FALSE(input.Keyboard().isKeyUp(Key::A));
}

TEST_F(InputSuite, GetKeyUp_A) {
    Input input;
    KeyboardInputInjector injector(input.Keyboard());

    injector.beginFrame();
    injector.onKeyPressed(Key::A);
    
    ASSERT_TRUE(input.Keyboard().isKeyDown(Key::A));
    ASSERT_TRUE(input.Keyboard().isKeyHold(Key::A));
    ASSERT_FALSE(input.Keyboard().isKeyUp(Key::A));

    injector.beginFrame();
    injector.onKeyReleased(Key::A);
    
    ASSERT_FALSE(input.Keyboard().isKeyDown(Key::A));
    ASSERT_FALSE(input.Keyboard().isKeyHold(Key::A));
    ASSERT_TRUE(input.Keyboard().isKeyUp(Key::A));
}

TEST_F(InputSuite, KeyPressedTwice) {
    Input input;
    KeyboardInputInjector injector(input.Keyboard());

    injector.beginFrame();
    injector.onKeyPressed(Key::A);
    injector.onKeyPressed(Key::A);
    
    ASSERT_TRUE(input.Keyboard().isKeyDown(Key::A));
    ASSERT_TRUE(input.Keyboard().isKeyHold(Key::A));
    ASSERT_FALSE(input.Keyboard().isKeyUp(Key::A));
}

TEST_F(InputSuite, KeyReleasedTwice) {
    Input input;
    KeyboardInputInjector injector(input.Keyboard());

    injector.beginFrame();
    injector.onKeyPressed(Key::A);
    
    injector.beginFrame();
    injector.onKeyReleased(Key::A);
    injector.onKeyReleased(Key::A);
    
    ASSERT_FALSE(input.Keyboard().isKeyDown(Key::A));
    ASSERT_FALSE(input.Keyboard().isKeyHold(Key::A));
    ASSERT_TRUE(input.Keyboard().isKeyUp(Key::A));
}

TEST_F(InputSuite, KeyReleasedButNotPressBefore) {
    Input input;
    KeyboardInputInjector injector(input.Keyboard());
    
    injector.beginFrame();
    injector.onKeyReleased(Key::A);
    
    ASSERT_FALSE(input.Keyboard().isKeyDown(Key::A));
    ASSERT_FALSE(input.Keyboard().isKeyHold(Key::A));
    ASSERT_TRUE(input.Keyboard().isKeyUp(Key::A));
}

TEST_F(InputSuite, KeyPressedThenReleasedInSameFrame) {
    Input input;
    KeyboardInputInjector injector(input.Keyboard());
    
    injector.beginFrame();
    injector.onKeyPressed(Key::A);
    injector.onKeyReleased(Key::A);
    
    ASSERT_FALSE(input.Keyboard().isKeyDown(Key::A));
    ASSERT_FALSE(input.Keyboard().isKeyHold(Key::A));
    ASSERT_TRUE(input.Keyboard().isKeyUp(Key::A));
}

TEST_F(InputSuite, KeyReleasedThenPressedInSameFrame) {
    Input input;
    KeyboardInputInjector injector(input.Keyboard());
    
    injector.beginFrame();
    injector.onKeyReleased(Key::A);
    injector.onKeyPressed(Key::A);
    
    ASSERT_TRUE(input.Keyboard().isKeyDown(Key::A));
    ASSERT_TRUE(input.Keyboard().isKeyHold(Key::A));
    ASSERT_FALSE(input.Keyboard().isKeyUp(Key::A));
}

TEST_F(InputSuite, MouseBeginFrame) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();

    for (int i = static_cast<int>(MouseKey::FIRST); i <= static_cast<int>(MouseKey::LAST); i++) {
        ASSERT_FALSE(input.Mouse().isMouseButtonDown(static_cast<MouseKey>(i)));
        ASSERT_FALSE(input.Mouse().isMouseButtonHold(static_cast<MouseKey>(i)));
        ASSERT_FALSE(input.Mouse().isMouseButtonUp(static_cast<MouseKey>(i)));
    }
}

TEST_F(InputSuite, MouseGetButtonDown_LEFT) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onMouseButtonPressed(MouseKey::LEFT);
    
    ASSERT_TRUE(input.Mouse().isMouseButtonDown(MouseKey::LEFT));
    ASSERT_TRUE(input.Mouse().isMouseButtonHold(MouseKey::LEFT));
    ASSERT_FALSE(input.Mouse().isMouseButtonUp(MouseKey::LEFT));
}

TEST_F(InputSuite, MouseGetButtonPress_LEFT) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onMouseButtonPressed(MouseKey::LEFT);
    
    ASSERT_TRUE(input.Mouse().isMouseButtonDown(MouseKey::LEFT));
    ASSERT_TRUE(input.Mouse().isMouseButtonHold(MouseKey::LEFT));
    ASSERT_FALSE(input.Mouse().isMouseButtonUp(MouseKey::LEFT));

    injector.beginFrame();
    
    ASSERT_FALSE(input.Mouse().isMouseButtonDown(MouseKey::LEFT));
    ASSERT_TRUE(input.Mouse().isMouseButtonHold(MouseKey::LEFT));
    ASSERT_FALSE(input.Mouse().isMouseButtonUp(MouseKey::LEFT));
}

TEST_F(InputSuite, MouseGetButtonUp_LEFT) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onMouseButtonPressed(MouseKey::LEFT);
    
    ASSERT_TRUE(input.Mouse().isMouseButtonDown(MouseKey::LEFT));
    ASSERT_TRUE(input.Mouse().isMouseButtonHold(MouseKey::LEFT));
    ASSERT_FALSE(input.Mouse().isMouseButtonUp(MouseKey::LEFT));

    injector.beginFrame();
    injector.onMouseButtonReleased(MouseKey::LEFT);
    
    ASSERT_FALSE(input.Mouse().isMouseButtonDown(MouseKey::LEFT));
    ASSERT_FALSE(input.Mouse().isMouseButtonHold(MouseKey::LEFT));
    ASSERT_TRUE(input.Mouse().isMouseButtonUp(MouseKey::LEFT));
}

TEST_F(InputSuite, MouseButtonPressedTwice) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onMouseButtonPressed(MouseKey::LEFT);
    injector.onMouseButtonPressed(MouseKey::LEFT);
    
    ASSERT_TRUE(input.Mouse().isMouseButtonDown(MouseKey::LEFT));
    ASSERT_TRUE(input.Mouse().isMouseButtonHold(MouseKey::LEFT));
    ASSERT_FALSE(input.Mouse().isMouseButtonUp(MouseKey::LEFT));
}

TEST_F(InputSuite, MouseButtonReleasedTwice) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onMouseButtonPressed(MouseKey::LEFT);

    injector.beginFrame();
    injector.onMouseButtonReleased(MouseKey::LEFT);
    injector.onMouseButtonReleased(MouseKey::LEFT);
}

TEST_F(InputSuite, MouseButtonReleasedButNotPressBefore) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onMouseButtonReleased(MouseKey::LEFT);
    
    ASSERT_FALSE(input.Mouse().isMouseButtonDown(MouseKey::LEFT));
    ASSERT_FALSE(input.Mouse().isMouseButtonHold(MouseKey::LEFT));
    ASSERT_TRUE(input.Mouse().isMouseButtonUp(MouseKey::LEFT));
}

TEST_F(InputSuite, MouseButtonPressedThenReleasedInSameFrame) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onMouseButtonPressed(MouseKey::LEFT);
    injector.onMouseButtonReleased(MouseKey::LEFT);
    
    ASSERT_FALSE(input.Mouse().isMouseButtonDown(MouseKey::LEFT));
    ASSERT_FALSE(input.Mouse().isMouseButtonHold(MouseKey::LEFT));
    ASSERT_TRUE(input.Mouse().isMouseButtonUp(MouseKey::LEFT));
}

TEST_F(InputSuite, MouseButtonReleasedThenPressedInSameFrame) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onMouseButtonReleased(MouseKey::LEFT);
    injector.onMouseButtonPressed(MouseKey::LEFT);
    
    ASSERT_TRUE(input.Mouse().isMouseButtonDown(MouseKey::LEFT));
    ASSERT_TRUE(input.Mouse().isMouseButtonHold(MouseKey::LEFT));
    ASSERT_FALSE(input.Mouse().isMouseButtonUp(MouseKey::LEFT));
}

TEST_F(InputSuite, CursorPositionUpdate) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onCursorMoved({ .x = 5, .y = 7 });

    ASSERT_EQ(5, input.Mouse().Pos().x);
    ASSERT_EQ(7, input.Mouse().Pos().y);
}

TEST_F(InputSuite, CursorPositionWontResetWhenBeginFrame) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onCursorMoved({ .x = 5, .y = 7 });

    injector.beginFrame();

    ASSERT_EQ(5, input.Mouse().Pos().x);
    ASSERT_EQ(7, input.Mouse().Pos().y);
}

TEST_F(InputSuite, MouseScrollOffsetUpdate) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onScrollScrolled({ .x = 5, .y = -3 });

    ASSERT_EQ(5, input.Mouse().ScrollOffset().x);
    ASSERT_EQ(-3, input.Mouse().ScrollOffset().y);
}

TEST_F(InputSuite, MouseScrollOffsetResetWhenBeginFrame) {
    Input input;
    MouseInputInjector injector(input.Mouse());

    injector.beginFrame();
    injector.onScrollScrolled({ .x = 5, .y = -3 });

    injector.beginFrame();

    ASSERT_EQ(0, input.Mouse().ScrollOffset().x);
    ASSERT_EQ(0, input.Mouse().ScrollOffset().y);

}
