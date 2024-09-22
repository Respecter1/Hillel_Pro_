import QtQuick
import QtQuick.Controls

Window {
    maximumHeight: 480
    maximumWidth: 440
    minimumHeight: 480
    minimumWidth: 440
    visible: true
    title: qsTr("Calculator")
    color: "green"

    property string input: ""

    TextInput {
        id: inputField
        width: parent.width - 10
        height: 50
        visible: true
        font.pixelSize: 24
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        readOnly: true
        font.family: "Timmana"
        font.pointSize: 14
        color: "black"
        text: input
    }

    Text {
        id: resultField
        width: parent.width
        height: 50
        font.pixelSize: 24
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        anchors.top: inputField.bottom // Розташувати результат під полем вводу
        anchors.left: parent.left
        anchors.right: parent.right
        color: "black"
    }

    Rectangle {
        id: board
        width: 440
        height: 280
        x: 0
        y: 200
        visible: true

        Button {
            id: escapes
            width: 50
            height: 40
            x: 10
            y: 20
            text: "clear"
            onClicked: {
                input = ""
                resultField.text = ""
            }
        }
        Button {
            id: start_block
            width: 50
            height: 40
            x: 65
            y: 20
            text: "("
            onClicked: input += "("
        }
        Button {
            id: finish_block
            width: 50
            height: 40
            x: 120
            y: 20
            text: ")"
            onClicked: input += ")"
        }
        Button {
            id: divide
            width: 50
            height: 40
            x: 175
            y: 20
            text: "/"
            onClicked: input += "/"
        }
        Button {
            id: seven
            width: 50
            height: 40
            x: 10
            y: 65
            text: "7"
            onClicked: input += "7"
        }
        Button {
            id: eight
            width: 50
            height: 40
            x: 65
            y: 65
            text: "8"
            onClicked: input += "8"
        }
        Button {
            id: nine
            width: 50
            height: 40
            x: 120
            y: 65
            text: "9"
            onClicked: input += "9"
        }
        Button {
            id: multiply
            width: 50
            height: 40
            x: 175
            y: 65
            text: "*"
            onClicked: input += "*"
        }
        Button {
            id: four
            width: 50
            height: 40
            x: 10
            y: 110
            text: "4"
            onClicked: input += "4"
        }
        Button {
            id: five
            width: 50
            height: 40
            x: 65
            y: 110
            text: "5"
            onClicked: input += "5"
        }
        Button {
            id: six
            width: 50
            height: 40
            x: 120
            y: 110
            text: "6"
            onClicked: input += "6"
        }
        Button {
            id: minus
            width: 50
            height: 40
            x: 175
            y: 110
            text: "-"
            onClicked: input += "-"
        }
        Button {
            id: one
            width: 50
            height: 40
            x: 10
            y: 155
            text: "1"
            onClicked: input += "1"
        }
        Button {
            id: two
            width: 50
            height: 40
            x: 65
            y: 155
            text: "2"
            onClicked: input += "2"
        }
        Button {
            id: three
            width: 50
            height: 40
            x: 120
            y: 155
            text: "3"
            onClicked: input += "3"
        }
        Button {
            id: plus
            width: 50
            height: 40
            x: 175
            y: 155
            text: "+"
            onClicked: input += "+"
        }
        Button {
            id: zero
            width: 50
            height: 40
            x: 10
            y: 200
            text: "0"
            onClicked: input += "0"
        }
        Button {
            id: dot
            width: 50
            height: 40
            x: 65
            y: 200
            text: "."
            onClicked: input += "."
        }
        Button {
            id: equals
            width: 50
            height: 40
            x: 175
            y: 200
            text: "="

            onClicked: {
                try {
                    resultField.text = evaluate(input)
                } catch (e) {
                    resultField.text = "Error"
                }
            }
        }
    }

    function evaluate(expression) {
        try {
            // Обрізаємо пробіли
            expression = expression.replace(/\s+/g, "")

            // Перевірка виразу на допустимі символи
            if (/[^0-9+\-*/().]/.test(expression)) {
                throw "Invalid expression"
            }

            // Оцінюємо вираз
            return new Function("return " + expression)()
        } catch (e) {
            return "Error"
        }
    }
}
