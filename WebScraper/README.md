# Web Scraper

A simple Python web scraper that collects information from a web page and saves the extracted data to text files.

The project uses **Requests** to retrieve the web page and **BeautifulSoup** to parse its HTML structure.

## Features

- Send an HTTP request to a web page
- Parse HTML content
- Extract headings (`h1`–`h6`)
- Extract paragraphs (`p`)
- Count extracted elements
- Save headings to a text file
- Save paragraphs to a text file

## Technologies

- **Python**
- **Requests**
- **BeautifulSoup**

## How It Works

The scraper:

1. Sends a request to the specified URL.
2. Checks the HTTP response status.
3. Parses the returned HTML using BeautifulSoup.
4. Finds all headings.
5. Saves the headings to `headings_all.txt`.
6. Finds all paragraphs.
7. Saves the paragraphs to `paragraphs.txt`.

## Output

The application creates two text files:

```text
headings_all.txt
paragraphs.txt