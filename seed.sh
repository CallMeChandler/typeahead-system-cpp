#!/bin/bash

URL="http://localhost:18080/words"

add_word() {
    curl -s -X POST "$URL" \
        -H "Content-Type: application/json" \
        -d "{\"word\":\"$1\"}" > /dev/null
}

# ============================================================
# PROGRAMMING
# ============================================================

for word in \
algorithm algorithms array arrays \
backend backends frontend frontends \
database databases datastore \
developer developers development \
debug debugging debugger \
docker documentation \
framework frameworks \
function functions \
github git \
javascript java \
python programming programmer \
typescript \
compiler compilation \
coding code \
software system systems \
server servers \
client clients \
api apis \
http https \
request requests response responses \
network networking \
security secure \
authentication authorization \
microservice microservices \
architecture \
design designer \
testing test tester \
deployment deploy \
cloud \
linux \
terminal \
kubernetes \
container containers \
repository repositories \
branch branches \
commit commits \
merge \
pull \
push \
build \
library libraries \
package packages \
module modules \
class classes \
object objects \
interface interfaces \
inheritance \
polymorphism \
template templates \
pointer pointers \
memory \
thread threads \
process processes \
queue queues \
stack stacks \
tree trees \
graph graphs \
hashmap \
database \
sql \
query queries \
transaction transactions \
index indexes \
cache caching \
redis \
mongodb \
postgresql \
mysql \
aws \
azure \
google \
amazon \
microsoft
do
    add_word "$word"
done


# ============================================================
# AI / ML
# ============================================================

for word in \
ai \
artificial \
artificialintelligence \
machine \
machinelearning \
learning \
deep \
deeplearning \
neural \
neuralnetwork \
networks \
model \
models \
training \
trainer \
inference \
prediction \
predictive \
classification \
classifier \
regression \
clustering \
transformer \
transformers \
llm \
llms \
language \
natural \
naturallanguage \
nlp \
computer \
vision \
computervision \
tensorflow \
pytorch \
keras \
scikit \
python \
numpy \
pandas \
data \
dataset \
datasets \
analytics \
analysis \
statistics \
embedding \
embeddings \
vector \
vectors \
vectorsearch \
rag \
retrieval \
generation \
generative \
prompt \
prompts \
agent \
agents
do
    add_word "$word"
done


# ============================================================
# COMMON ENGLISH WORDS
# ============================================================

for word in \
apple application apply applicant appointment \
appreciate approach appropriate approval \
banana band bank basketball battle \
camera camp camping campus candle candy \
car card career careful carry cartoon case \
cat category catch cause center central century \
computer company complete condition connection \
control conversation country course create creation \
customer database date day decision developer \
development device digital direction document \
education email employee environment event example \
experience feature file finance final food football \
game github google government group \
health history home house human \
idea image information internet interview \
job journey json \
key knowledge \
language laptop large learning life link linux \
machine management manager market material \
media message method mobile money \
name network news number \
object office operation opportunity order \
page password people performance person \
phone photo picture platform player \
point policy price problem process product \
program project question queue \
react read real request result \
school search security service server \
software solution source space speed \
sport student study system \
table technology test testing text \
time tool topic total \
training travel tree type \
user username \
value video view \
website window work world \
year
do
    add_word "$word"
done


# ============================================================
# TECH PREFIX TESTING
# ============================================================

for word in \
car card care career careful cargo cartoon \
cam camera cameras camping campus campaign \
cat cats category categories catch catcher \
can candy candle candles candidate candidates \
app apple apples application applications \
apply applied applicant applicants appointment \
back backend backends backup background \
ban banana bananas band bandwidth bank banking \
dev developer developers development developing \
devi device devices \
des design designer designers destination \
dat data database databases dataset datasets \
do docker documentation document documents \
goo google googlecloud good \
git github githubactions gitlab \
jav java javascript javascriptengine \
py python pytorch pyramid \
mac machine machines macbook \
mic microsoft microphone microservice \
neu neural network networking \
pro programming programmer program project product \
rea react reactive read reader real realtime \
sys system systems syntax \
tes test testing tester \
tra training transaction transfer travel \
use user username users
do
    add_word "$word"
done


# ============================================================
# HIGH-FREQUENCY WORDS
# These intentionally occur many times.
# ============================================================

for i in {1..25}; do
    add_word "google"
done

for i in {1..20}; do
    add_word "github"
done

for i in {1..18}; do
    add_word "python"
done

for i in {1..16}; do
    add_word "javascript"
done

for i in {1..15}; do
    add_word "java"
done

for i in {1..14}; do
    add_word "database"
done

for i in {1..13}; do
    add_word "developer"
done

for i in {1..12}; do
    add_word "development"
done

for i in {1..11}; do
    add_word "backend"
done

for i in {1..10}; do
    add_word "frontend"
done

for i in {1..9}; do
    add_word "machine"
done

for i in {1..8}; do
    add_word "learning"
done

for i in {1..7}; do
    add_word "programming"
done

for i in {1..6}; do
    add_word "project"
done

for i in {1..5}; do
    add_word "system"
done

echo "Seed complete!"