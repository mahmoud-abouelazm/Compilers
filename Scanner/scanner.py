import re
import tkinter as tk
from tkinter import scrolledtext

# Function to scan input code and classify tokens
def scan_code():
    code = text_area.get("1.0", tk.END)

    # Regular expressions for each token type, including binary and shift operators
    token_patterns = [
        (r"//.*", "comment"),  # Single-line comment
        (r"/\*[\s\S]*?\*/", "comment"),  # Multi-line comment
        (r"\b(int|float|char|if|else|for|while|return)\b", "keyword"),  # Keywords
        (r"[a-zA-Z_]\w*", "identifier"),  # Identifiers
        (r"[+\-*/=<>!]=?|&&|\|\||&|\||\^|<<|>>", "operator"),  # Operators including binary and shift
        (r"\b\d+(\.\d+)?(e[+-]?\d+)?\b", "numeric_constant"),  # Numeric constants with scientific notation
        (r"'.?'", "character_constant"),  # Character constants
        (r'"[^"]*"', "string"),  # Strings
        (r"[{}()\[\];,]", "special_character"),  # Special characters
        (r"\n", "newline"),  # Newlines (if you need them, otherwise remove this line)
    ]

    # List to store tokens
    tokens = []

    # Loop through code to match tokens
    while code:
        match = None
        for pattern, token_type in token_patterns:
            regex = re.compile(pattern)
            match = regex.match(code)
            if match:
                token_value = match.group(0)
                # Skip whitespace tokens in output
                if token_type != "whitespace":
                    tokens.append((token_type, token_value))
                code = code[len(token_value):]
                break
        if not match:  # If no pattern matches, move one character forward
            code = code[1:]

    # Display results in the output area
    output_area.delete("1.0", tk.END)
    for token_type, token_value in tokens:
        output_area.insert(tk.END, f"({token_type}, '{token_value}')\n")

# Setup tkinter window
root = tk.Tk()
root.geometry("800x600")  # Set the window size to 800x600

# Title Label
title_label = tk.Label(
    root,
    text="C Language Syntax Scanner",
    font=("Helvetica", 18, "bold"),
    fg="#f8f9fa",
    bg="#2e3b4e",
)
title_label.grid(row=0, column=0, columnspan=2, pady=20)

# Input text area (with a soft blue background)
text_area = scrolledtext.ScrolledText(
    root,
    width=60,
    height=15,
    font=("Courier New", 12),
    wrap=tk.WORD,
    bg="#f0f8ff",
    fg="#000000",
    bd=2,
    relief="sunken",
)
text_area.grid(row=1, column=0, padx=10, pady=10)
text_area.insert(tk.END, "/* Enter your code here */")

# Output text area (with a light yellow background)
output_area = scrolledtext.ScrolledText(
    root,
    width=60,
    height=15,
    font=("Courier New", 12),
    wrap=tk.WORD,
    bg="#fffacd",
    fg="#000000",
    bd=2,
    relief="sunken",
)
output_area.grid(row=1, column=1, padx=10, pady=10)

# Button to scan code (styled with a modern look)
scan_button = tk.Button(
    root,
    text="Scan Code",
    command=scan_code,
    font=("Helvetica", 14, "bold"),
    fg="#ffffff",
    bg="#4CAF50",
    relief="raised",
    bd=4,
    width=15,
)
scan_button.grid(row=2, column=0, columnspan=2, pady=20)

# Adding a border with a shadow effect for the window
root.config(bd=10, relief="solid", bg="#2e3b4e")

# Run the Tkinter window
root.mainloop()
