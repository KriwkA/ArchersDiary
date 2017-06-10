import QtQuick 2.5
import QtQml 2.2
import QtQuick.Controls 2.1


SpinBox{
    property int decimals: 2
    property double realValue: 0.0
    property double realFrom: 0.0
    property double realTo: 100.0
    property double realStepSize: 1.0
    property double factor: Math.pow(10, decimals)

    id: spinbox
    stepSize: realStepSize*factor
    value: realValue*factor
    to : realTo*factor
    from : realFrom*factor

    validator: DoubleValidator {
        bottom: Math.min(spinbox.from, spinbox.to)*spinbox.factor
        top:  Math.max(spinbox.from, spinbox.to)*spinbox.factor
        decimals: decimals
    }

    textFromValue: function(value, locale) {       
        return Number( valueToReal( value ) ).toLocaleString(locale, 'f', decimals );
    }

    valueFromText: function(text, locale) {        
        return realToValue(Number.fromLocaleText(locale, text));
    }

    function realToValue(real) {
        return real * factor;
    }

    function valueToReal(val) {
        return val * 1.0 / factor;
    }

    onValueChanged: {
        realValue = valueToReal(value);
    }
}
