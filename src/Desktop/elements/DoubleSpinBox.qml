import QtQuick 2.7
import QtQuick.Controls 2.1

SpinBox {
    editable: true;
    id: spin

    property int decimals: 2
    property double factor: Math.pow(10.0, decimals)

    property double realFrom: 0.0
    from: realFrom * factor;

    property double realTo: 100.0
    to: realTo * factor;

    property double realValue: 1.0
    value: realValue * factor

    property double realStepSize: 0.1
    stepSize: realStepSize * factor

    valueFromText: function( txt, loc ) {
        return Number.fromLocaleString(loc, txt) * factor;
    }

    textFromValue: function( val, loc ) {
        return Number( val * 1.0 / factor ).toLocaleString(loc, 'f', decimals)
    }

    validator: DoubleValidator {
        id: validatorSpin
        decimals: spin.decimals
        notation: DoubleValidator.StandardNotation
        top: Math.max(spin.from, spin.to) / spin.factor
        bottom: Math.min(spin.from, spin.to) / spin.factor
    }

    Keys.onReturnPressed: {
        Qt.inputMethod.hide();
    }

    onValueChanged: {
        realValue = value * 1.0 / factor;
    }
}
