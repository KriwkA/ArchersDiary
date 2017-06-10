import QtQuick 2.5
import QtQml 2.2
import QtQuick.Controls 2.1


SpinBox{
    property int decimals: 2
    property real realValue: 0.0
    property real realFrom: 0.0
    property real realTo: 100.0
    property real realStepSize: 1.0
    property real factor: Math.pow(10, decimals)
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
        var realVal = value * 1.0 / factor;
        var res = Number( realVal ).toLocaleString(locale, 'f', decimals );
        return res;
    }

    valueFromText: function(text, locale) {
        var realVal = Number.fromLocaleText(locale, text);
        var val = realVal * factor;
        console.log("ValFromText");
        console.log(text);
        console.log(realVal);
        console.log(val);
        return val;
    }

}
