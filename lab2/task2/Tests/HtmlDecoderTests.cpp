#define CATCH_CONFIG_MAIN

#include "../../../libs/catch2/catch.hpp"
#include "../HtmlDecoder/HtmlDecoder.h"
#include <limits>

SCENARIO("HtmlDecode")
{
	WHEN("Input string is empty")
	{
		std::string input, output;
		THEN("Output string is also empty")
		{
			output = HtmlDecode(input);
			CHECK(output.empty());
		}
	}

	WHEN("Input string doesn't contain specific symbols")
	{
		std::string input = R"(
	Lorem ipsum dolor sit amet, consectetur adipiscing elit.
Duis placerat convallis massa, eu consectetur arcu tristique at.
Suspendisse egestas, tellus in condimentum posuere, erat diam vulputate
leo, ac consectetur mi ante at risus.

	Nunc risus tellus, tincidunt ac
ex eget, laoreet blandit urna. Sed finibus risus metus, lobortis
ullamcorper turpis vehicula quis. Fusce id bibendum dui. In eget
porta elit, ut porttitor felis. Vestibulum ante ipsum primis in
faucibus orci luctus et ultrices posuere.

	Cubilia curae;
Phasellus quis posuere lectus, et aliquet urna. Proin cursus sapien
ut iaculis feugiat. Aliquam volutpat metus dignissim lectus dapibus,
eu hendrerit nunc molestie.)";
		THEN("Output string is equal to input string")
		{
			REQUIRE(HtmlDecode(input) == input);
		}
	}

	WHEN ("Input string contains only specific symbols in HTML code")
	{
		std::string input = R"(
&gt;&quot;&gt;&quot;&gt;&gt;&gt;&quot;&gt;&lt;
&gt;&quot;&gt;&gt;&gt;&gt;&gt;&gt;&apos;&gt;&gt;&apos;
&apos;&apos;&apos;&apos;&apos;&lt;&apos;&lt;&lt;
&apos;&apos;&apos;&gt;&apos&gt;;&apos;&lt;&lt;&lt;&amp;
&amp;&amp;&lt;&lt;&lt;&amp;&amp;&amp;&lt;&lt;&lt;&lt;
&gt;&amp;&amp;&gt;&gt;&gt;&amp;)";
		std::string expectedOutput = R"(
>">">>>"><
>">>>>>>'>>'
'''''<'<<
'''>&apos>;'<<<&
&&<<<&&&<<<<
>&&>>>&)";
		THEN("Output string contains converted specific characters in normal form")
		{
			REQUIRE(expectedOutput == HtmlDecode(input));
		}
	}

	WHEN ("Input string contains both regular characters and special characters in HTML code") {
		std::string input(R"(
<body>
&quot;Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean
scelerisque vitae nibh sit amet semper. Ut &lt;luctus&gt; massa urna,
nec porttitor enim aliquet&apos;vel. Aliquam vitae&apos; rhoncus ante.
Fusce sed ex quis magna bibendum dignissim. Ut tempor et magna ut elementum.
Nulla et convallis velit. Curabitur suscipit ac risus in suscipit.&quot;
</body>)");
		std::string expectedOutput(R"(
<body>
"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean
scelerisque vitae nibh sit amet semper. Ut <luctus> massa urna,
nec porttitor enim aliquet'vel. Aliquam vitae' rhoncus ante.
Fusce sed ex quis magna bibendum dignissim. Ut tempor et magna ut elementum.
Nulla et convallis velit. Curabitur suscipit ac risus in suscipit."
</body>)");
		THEN("Output string contains regular characters and special characters in normal form")
		{
			REQUIRE(expectedOutput == HtmlDecode(input));
		}
	}
}