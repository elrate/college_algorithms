import 'package:flutter/material.dart';

class Button extends StatelessWidget {
  static const DARK = Color.fromRGBO(11, 6, 53, 1);
  static const DEFAULT = Color.fromRGBO(43, 44, 40, 1);
  static const OPERATION = Color.fromRGBO(0, 0, 205, 1);

  final String text;
  final bool big;
  final Color color;
  final void Function(String) cb;

  Button({
    required this.text,
    this.big = false,
    this.color = DEFAULT,
    required this.cb,
  });

    Button.big({
    required this.text,
    this.big = true,
    this.color = DEFAULT,
    required this.cb,
  });

    Button.operation({
    required this.text,
    this.big = false,
    this.color = OPERATION,
    required this.cb,
  });

  @override
  Widget build(BuildContext context) {
    return Expanded(
      flex: big ? 2 : 1, //Expanda de forma igual
      child: ElevatedButton(
        style: ElevatedButton.styleFrom(
          //primary: this.color, //primary segundo a IDE esta depreciada
          backgroundColor: this.color,
       ),
        child: Text(
          text,
          style: TextStyle(
            color: Colors.white,
            fontSize: 32,
            fontWeight: FontWeight.w200,
          ),
        ),
        onPressed: () => cb(text),
      ),
    );
  }
}
