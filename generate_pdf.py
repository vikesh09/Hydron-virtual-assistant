import os
from reportlab.lib.pagesizes import letter
from reportlab.lib import colors
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Table, TableStyle, HRFlowable

def create_pdf(filename):
    doc = SimpleDocTemplate(
        filename,
        pagesize=letter,
        rightMargin=40,
        leftMargin=40,
        topMargin=40,
        bottomMargin=40
    )

    styles = getSampleStyleSheet()
    
    # Custom styles
    title_style = ParagraphStyle(
        'DocTitle',
        parent=styles['Heading1'],
        fontName='Helvetica-Bold',
        fontSize=20,
        leading=24,
        textColor=colors.HexColor('#1E293B'),
        alignment=1, # Center
        spaceAfter=15
    )

    subtitle_style = ParagraphStyle(
        'DocSubtitle',
        parent=styles['Normal'],
        fontName='Helvetica-Oblique',
        fontSize=11,
        leading=14,
        textColor=colors.HexColor('#475569'),
        alignment=1,
        spaceAfter=20
    )

    heading_style = ParagraphStyle(
        'FuncHeading',
        parent=styles['Heading2'],
        fontName='Helvetica-Bold',
        fontSize=13,
        leading=16,
        textColor=colors.HexColor('#0F172A'),
        spaceBefore=12,
        spaceAfter=6
    )

    body_style = ParagraphStyle(
        'BodyTextCustom',
        parent=styles['Normal'],
        fontName='Helvetica',
        fontSize=9.5,
        leading=13,
        textColor=colors.HexColor('#334155'),
        spaceAfter=6
    )

    bold_label = ParagraphStyle(
        'BoldLabel',
        parent=body_style,
        fontName='Helvetica-Bold',
        textColor=colors.HexColor('#1E293B')
    )

    story = []

    # Title & Subtitle
    story.append(Paragraph("HYDRON VIRTUAL ASSISTANT", title_style))
    story.append(Paragraph("Detailed Guide: Working of 6 Core Functions & Technical Architecture", subtitle_style))
    story.append(HRFlowable(width="100%", thickness=1.5, color=colors.HexColor('#2563EB'), spaceAfter=15))

    functions_data = [
        {
            "num": "1",
            "name": "time / date (System Clock Query)",
            "command": "time  OR  date",
            "class_file": "TimeTask (TimeTask.h, TimeTask.cpp)",
            "oop_concept": "Inheritance & Dynamic Polymorphism",
            "working": "Jab user 'time' ya 'date' type karta hai, CommandParser TimeTask ka instance return karta hai. TimeTask::execute() C++ std::chrono::system_clock::now() aur std::localtime() se system time fetch karta hai. Formatted output (YYYY-MM-DD HH:MM:SS) console par print karta hai."
        },
        {
            "num": "2",
            "name": "open <app> (Desktop App Launcher)",
            "command": "open notepad  /  open calc  /  open safari",
            "class_file": "OpenAppTask (OpenAppTask.h, OpenAppTask.cpp)",
            "oop_concept": "Inheritance, Polymorphism, Platform Abstraction",
            "working": "User se application ka naam (argument) leta hai. Windows par std::system(\"start <app>\") execute karta hai. Mac OS par smart aliases use karta hai (notepad -> TextEdit, calc -> Calculator) aur open -a command se application ko background me launch karta hai."
        },
        {
            "num": "3",
            "name": "search <query> (Web Search Automation)",
            "command": "search C++ OOP concepts",
            "class_file": "SearchTask (SearchTask.h, SearchTask.cpp)",
            "oop_concept": "Inheritance, Encapsulation, Helper Encoding",
            "working": "Search query ke spaces ko urlEncodeQuery() helper function se '+' me convert karta hai. Phir formatted URL (https://www.google.com/search?q=...) banakar system default web browser me launch kar deta hai."
        },
        {
            "num": "4",
            "name": "new tab (Keyboard Shortcut Automation)",
            "command": "new tab",
            "class_file": "NewTabTask (NewTabTask.h, NewTabTask.cpp)",
            "oop_concept": "Inheritance & Win32 API Integration",
            "working": "Windows Win32 SendInput() API ka use karke 4 keyboard input structures ka array inject karta hai: (1) VK_CONTROL press, (2) 'T' key press, (3) 'T' key release, (4) VK_CONTROL release. Isse browser me Ctrl+T new tab shortcut simulate hota hai."
        },
        {
            "num": "5",
            "name": "history (Command Log Persistence)",
            "command": "history",
            "class_file": "HistoryTask & Logger (Logger.h, Logger.cpp)",
            "oop_concept": "File Handling (I/O Streams) & Encapsulation",
            "working": "Har executed command Logger class dwara [YYYY-MM-DD HH:MM:SS] timestamp ke sath history.txt me std::ofstream (std::ios::app mode) se log hota hai. 'history' command par HistoryTask Logger::printHistory() call karke std::ifstream se poori history display karta hai."
        },
        {
            "num": "6",
            "name": "exit / quit & help (Lifecycle & Assistance)",
            "command": "exit  /  quit  /  help",
            "class_file": "Assistant (Assistant.h, Assistant.cpp)",
            "oop_concept": "Encapsulation & REPL Control Loop",
            "working": "Assistant::run() ke main while-loop ko control karta hai. 'help' par saare supported commands ki menu list render hoti hai. 'exit' milne par isRunning boolean false ho jata hai aur farewell message dekar program cleanly exit karta hai."
        }
    ]

    for item in functions_data:
        story.append(Paragraph(f"Function {item['num']}: {item['name']}", heading_style))
        
        table_content = [
            [Paragraph("<b>Command:</b>", bold_label), Paragraph(f"<code>{item['command']}</code>", body_style)],
            [Paragraph("<b>Class & File:</b>", bold_label), Paragraph(item['class_file'], body_style)],
            [Paragraph("<b>OOP Concept:</b>", bold_label), Paragraph(f"<font color='#2563EB'><b>{item['oop_concept']}</b></font>", body_style)],
            [Paragraph("<b>How It Works:</b>", bold_label), Paragraph(item['working'], body_style)]
        ]

        t = Table(table_content, colWidths=[110, 420])
        t.setStyle(TableStyle([
            ('BACKGROUND', (0,0), (-1,-1), colors.HexColor('#F8FAFC')),
            ('GRID', (0,0), (-1,-1), 0.5, colors.HexColor('#E2E8F0')),
            ('VALIGN', (0,0), (-1,-1), 'TOP'),
            ('PADDING', (0,0), (-1,-1), 5),
        ]))
        
        story.append(t)
        story.append(Spacer(1, 10))

    # Architecture Overview Section
    story.append(HRFlowable(width="100%", thickness=1, color=colors.HexColor('#CBD5E1'), spaceBefore=10, spaceAfter=15))
    story.append(Paragraph("Summary Architecture Flow (Execution Pipeline)", heading_style))
    
    flow_text = "<b>User Input</b> &rarr; <b>Assistant::run()</b> &rarr; <b>Logger::logCommand()</b> (appends to history.txt) &rarr; <b>CommandParser::parse()</b> (validates & creates Task*) &rarr; <b>task-&gt;execute()</b> (Polymorphic call) &rarr; <b>Output rendered</b>."
    story.append(Paragraph(flow_text, body_style))

    doc.build(story)
    print(f"PDF successfully created: {filename}")

if __name__ == "__main__":
    create_pdf("/Users/whitemuffens/Desktop/Sem3/Oops/project_hydron-virtual/Hydron_6_Functions_Guide.pdf")
