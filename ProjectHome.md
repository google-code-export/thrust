<table align='center' border='0'>
<tr>
<td>
<a href='http://code.google.com/p/thrust/downloads/list'>
<img src='http://thrust.googlecode.com/hg/doc/thrust_logo.png' />
</a>
</td>
<td>

<table align='center' border='0'>
<tr><td align='center'>
<h1> What is Thrust?</h1>
</td></tr>
<tr><td>
<blockquote>Thrust is a parallel algorithms library which resembles the C++ Standard Template Library (STL). Thrust's <b>high-level</b> interface greatly enhances developer <b>productivity</b> while enabling performance portability between GPUs and multicore CPUs.  <b>Interoperability</b> with established technologies (such as CUDA, TBB and OpenMP) facilitates integration with existing software.  Develop <b>high-performance</b> applications rapidly with Thrust!</blockquote>

<blockquote>Read the <a href='QuickStartGuide.md'>Quick Start guide</a>.<br>
</td></tr>
</table>
</td>
</tr>
</table></blockquote>

# Github #

<font color='#FF0000'>We no longer maintain the Thrust project on Google Code. Find Thrust's new home at <a href='http://thrust.github.com'>thrust.github.com</a></font>

<br><br>

<h1>News</h1>
<ul><li>Thrust is now hosted on <a href='https://github.com/thrust/thrust'>Github</a>!<br>
</li><li>Thrust v1.6.0 has been <a href='http://code.google.com/p/thrust/downloads/list'>released!</a> Refer to the <a href='http://code.google.com/p/thrust/source/browse/CHANGELOG?name=1.6.0'>CHANGELOG</a> for changes since v1.5.1<br>
</li><li>Thrust v1.5.1 has been <a href='http://code.google.com/p/thrust/downloads/list'>released!</a>  Version 1.5.1 is distributed with CUDA 4.1 and fixes an uncommon sorting bug (see <a href='http://code.google.com/p/thrust/source/browse/CHANGELOG?name=1.5.1'>CHANGELOG</a>).<br>
</li><li>Thrust v1.5.0 has been <a href='http://code.google.com/p/thrust/downloads/list'>released!</a> Refer to the <a href='http://code.google.com/p/thrust/source/browse/CHANGELOG?name=1.5.0'>CHANGELOG</a> for changes since v1.4.0<br>
</li><li>Content from <a href='http://www.gputechconf.com/object/gtc-express-webinar.html'>Rapid Problem Solving Using Thrust</a> webinar is available (<a href='http://www.gputechconf.com/content/includes/gtc/video/stream-GTCthrust.html'>Stream</a>, <a href='http://developer.download.nvidia.com/CUDA/training/GTCthrust.mp4'>MP4</a>, <a href='http://developer.download.nvidia.com/CUDA/training/Rapid-Problem-Solving-Using-Thrust.pdf'>PDF</a>, <a href='http://developer.download.nvidia.com/CUDA/training/RapidProblemSolving.zip'>Code</a>)<br>
</li><li>Posted <a href='http://thrust.googlecode.com/files/Thrust%20-%20A%20Productivity-Oriented%20Library%20for%20CUDA.pdf'>Thrust chapter</a> from the upcoming <a href='http://mkp.com/news/3405'>GPU Computing Gems</a> book.<br>
</li><li>Thrust v1.4.0 has been <a href='http://code.google.com/p/thrust/downloads/list'>released!</a> Refer to the <a href='http://code.google.com/p/thrust/source/browse/CHANGELOG?name=1.4.0'>CHANGELOG</a> for changes since v1.3.0<br>
</li><li>Thrust v1.4.0 will be featured in the <a href='http://pressroom.nvidia.com/easyir/customrel.do?easyirid=A0D622CE9F579F09&version=live&prid=726171&releasejsp=release_157&xhtml=true'>CUDA 4.0 toolkit</a>
</li><li>Do your civic duty and fill out the <b><a href='https://spreadsheets.google.com/viewform?hl=en&formkey=dC1abTJNZFJsdzNEZnBTV3VsVUtKMEE6MA#gid=0'>2-minute Thrust user survey</a>!</b>.<br>
</li><li>Thrust v1.3.0 has been <a href='http://code.google.com/p/thrust/downloads/list'>released!</a> Refer to the <a href='http://code.google.com/p/thrust/source/browse/CHANGELOG?r=ccbb5cbacf0273bb7dc3f5a7023649053f2a7d80'>CHANGELOG</a> for changes since v1.2.1<br>
</li><li>GTC2010 presentations are <a href='http://www.nvidia.com/object/gtc2010-presentation-archive.html#session2219'>now online</a>.<br>
</li><li>Thrust v1.2.1 has been <a href='http://code.google.com/p/thrust/downloads/list'>released!</a> v1.2.1 contains compatibility fixes for CUDA 3.1.<br>
</li><li>Posted <a href='http://thrust.googlecode.com/files/An%20Introduction%20To%20Thrust.pdf'>An Introduction to Thrust</a> presentation.</li></ul>


<h1>Examples</h1>

Thrust is best explained through examples.  The following source code generates random numbers on the host and transfers them to the device where they are sorted.<br>
<br>
<pre><code>#include &lt;thrust/host_vector.h&gt;<br>
#include &lt;thrust/device_vector.h&gt;<br>
#include &lt;thrust/generate.h&gt;<br>
#include &lt;thrust/sort.h&gt;<br>
#include &lt;thrust/copy.h&gt;<br>
#include &lt;cstdlib&gt;<br>
<br>
int main(void)<br>
{<br>
    // generate 32M random numbers on the host<br>
    thrust::host_vector&lt;int&gt; h_vec(32 &lt;&lt; 20);<br>
    thrust::generate(h_vec.begin(), h_vec.end(), rand);<br>
<br>
    // transfer data to the device<br>
    thrust::device_vector&lt;int&gt; d_vec = h_vec;<br>
<br>
    // sort data on the device (846M keys per second on GeForce GTX 480)<br>
    thrust::sort(d_vec.begin(), d_vec.end());<br>
<br>
    // transfer data back to host<br>
    thrust::copy(d_vec.begin(), d_vec.end(), h_vec.begin());<br>
<br>
    return 0;<br>
}<br>
</code></pre>


This code sample computes the sum of 100 random numbers on the GPU.<br>
<pre><code>#include &lt;thrust/host_vector.h&gt;<br>
#include &lt;thrust/device_vector.h&gt;<br>
#include &lt;thrust/generate.h&gt;<br>
#include &lt;thrust/reduce.h&gt;<br>
#include &lt;thrust/functional.h&gt;<br>
#include &lt;cstdlib&gt;<br>
<br>
int main(void)<br>
{<br>
  // generate random data on the host<br>
  thrust::host_vector&lt;int&gt; h_vec(100);<br>
  thrust::generate(h_vec.begin(), h_vec.end(), rand);<br>
<br>
  // transfer to device and compute sum<br>
  thrust::device_vector&lt;int&gt; d_vec = h_vec;<br>
  int x = thrust::reduce(d_vec.begin(), d_vec.end(), 0, thrust::plus&lt;int&gt;());<br>
  return 0;<br>
}<br>
</code></pre>

Refer to the <a href='QuickStartGuide.md'>QuickStartGuide</a> page for further information and examples.<br>
<br>
<br>
<h1>Contributors</h1>

The primary developers of Thrust are <a href='http://research.nvidia.com/users/jared-hoberock'>Jared Hoberock</a> and <a href='http://research.nvidia.com/users/nathan-bell'>Nathan Bell</a>.  A complete list of contributors is available <a href='http://code.google.com/p/thrust/source/browse/THANKS'>here</a>.